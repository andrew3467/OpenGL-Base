#include "engine/ErrorManager.h"
#include "GLFW/glfw3.h"


#include "engine/GLPrimitives.h"
#include "engine/Camera.h"


#include "renderer/VertexBufferLayout.h"
#include "renderer/Shader.h"
#include "renderer/Texture2D.h"
#include "renderer/Texture3D.h"
#include "renderer/Renderer.h"

#include "ObjectData.h"

#include <imgui.h>
#include "../../external/imgui/examples/imgui_impl_glfw.h"
#include "../../external/imgui/examples/imgui_impl_opengl3.h"




#include <iostream>


int windowWidth = 1280;
int windowHeight = 720;
const char* windowTitle = "OpenGL Base";
GLFWwindow* window;

Renderer renderer;


Shader* colorShader;
Shader* lightingShader;
Shader* skyboxShader;

Camera* camera;
glm::mat4 projection;
glm::mat4 transform;

bool cursorEnabled = false;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void initGlFW();
void initGLAD();
void initObjects();

void processInput(GLFWwindow* window);

void update();
void tick();

//Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
    initGlFW();
    initGLAD();
    initObjects();

    GLErrorManager(glEnable(GL_DEPTH_TEST));
    GLErrorManager(glEnable(GL_PROGRAM_POINT_SIZE));
    GLErrorManager(glEnable(GL_FRAMEBUFFER_SRGB));

    GLErrorManager(glEnable(GL_BLEND));
    GLErrorManager(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Texture3D skyboxTex(faces);
    Texture2D woodTex("../../resources/textures/wood.png");
    Texture2D brickTex("../../resources/textures/brick.png");


    VertexArray cubeVA;
    VertexBuffer cubeVB(cubeVertices, sizeof(cubeVertices));
    IndexBuffer cubeIB(cubeIndices, 36);

    VertexBufferLayout cubeLayout;
    cubeLayout.Push<float>(3);
    cubeLayout.Push<float>(2);
    cubeVA.AddBuffer(cubeVB, cubeLayout);

    VertexArray planeVA;
    VertexBuffer planeVB(planeVertices, sizeof(planeVertices));
    IndexBuffer planeIB(planeIndices, 6);

    VertexBufferLayout planeLayout;
    planeLayout.Push<float>(3);
    planeLayout.Push<float>(3);
    planeLayout.Push<float>(2);
    planeVA.AddBuffer(planeVB, planeLayout);

    transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(1.0f));
    transform = glm::translate(transform, glm::vec3(0.0f, 2.0f, 0.0f));


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    const char* glsl_version = "#version 460";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    glm::vec3 cubePosition = glm::vec3(0.0f, 2.0f, 0.0f);


    //Disable cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLErrorManager(glViewport(0, 0, windowWidth, windowHeight));

    while(!glfwWindowShouldClose(window)) {
        processInput(window);


        GLErrorManager(glClearColor(0.05f, 0.05f, 0.05f, 1.0f));
        renderer.Clear();

        ImGui_ImplGlfw_NewFrame();


        //Floor
        lightingShader->Bind();
        woodTex.Bind();

        lightingShader->SetMat4("proj", projection);
        lightingShader->SetMat4("view", camera->view());

        lightingShader->SetInt("texture_diffuse0", 0);


        lightingShader->SetInt("numPointLights", numPointLights);
        for (unsigned int i = 0; i < numPointLights; ++i) {
            lightingShader->SetPointLight(pointLights[i], std::to_string(i));
        }

        lightingShader->SetVec3("viewPos", camera->position());
        lightingShader->SetFloat("shininess", 128.0f);

        lightingShader->SetInt("blinn", false);
        lightingShader->SetInt("gamma", true);

        transform = glm::mat4(1.0f);
        transform = glm::scale(transform, glm::vec3(20.0f, 1.0f, 20.0f));

        glPrimitive::DrawPlane(lightingShader, glm::vec3(0.0, 0.0, 0.0),
                               glm::vec3(20.0f, 1.0f, 20.0f));


        //Draw lights
        colorShader->Bind();

        colorShader->SetMat4("proj", projection);
        colorShader->SetMat4("view", camera->view());

        for (unsigned int i = 0; i < numPointLights; ++i) {
            transform = glm::mat4(1.0f);
            transform = glm::translate(transform, pointLights[i].position);
            transform = glm::scale(transform, glm::vec3(0.25f));

            colorShader->SetMat4("model", transform);
            colorShader->SetVec3("color", pointLights[i].ambient);
            renderer.Draw(colorShader, cubeVA, cubeIB);
        }

        colorShader->Unbind();

        //Draw Cubes
        colorShader->Bind();

        colorShader->SetMat4("proj", projection);
        colorShader->SetMat4("view", camera->view());

        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, cubePosition);
        transform = glm::scale(transform, glm::vec3(0.5f));
        transform = glm::rotate(transform, glm::radians(30.0f), cubeRotations[0]);

        colorShader->SetMat4("model", transform);
        colorShader->SetVec3("color", 0.3f, 0.5f, 0.8f);
        renderer.Draw(colorShader, cubeVA, cubeIB);

        colorShader->Unbind();



        // draw skybox as last
        skyboxShader->Bind();
        glm::mat4 view = glm::mat4(glm::mat3(camera->view()));
        skyboxShader->SetMat4("view", view);
        skyboxShader->SetMat4("projection", projection);

        skyboxTex.Bind();
        GLErrorManager(glDepthFunc(GL_LEQUAL));
        renderer.Draw(skyboxShader, cubeVA, cubeIB);
        GLErrorManager(glDepthFunc(GL_LESS));


        //ImGUI Windowing
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();


            {
                ImGui::Begin("FPS");

                ImGui::SetWindowSize({400, 100});

                ImGui::SliderFloat3("Cube Position", &cubePosition.x, 0.0f, 10.0f);

                ImGui::Spacing();
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }


            //Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }


        update();

        //auto data = ImGui::GetDrawData();

        tick();
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void initGlFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create glfw window\n";
        glfwTerminate();
        throw std::runtime_error("Failed to create glfw window\n");
    }
    glfwMakeContextCurrent(window);


    //GLFW callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
}

void initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD\n");
    }
}

void initObjects() {
    lightingShader = new Shader("../../src/shaders/texturedLit.vert", "../../src/shaders/texturedLit.frag");
    colorShader = new Shader("../../src/shaders/solidColor.vert", "../../src/shaders/solidColor.frag");
    skyboxShader = new Shader("../../src/shaders/skybox.vert", "../../src/shaders/skybox.frag");

    camera = new Camera(cameraPosition, windowWidth, windowHeight);
}



void processInput(GLFWwindow *window) {
    //Toggle Cursor
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        cursorEnabled = !cursorEnabled;
        int mode = cursorEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
        glfwSetInputMode(window, GLFW_CURSOR, mode);
    }


    //Camera Input
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->Move(Forward, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->Move(Backward, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->Move(Left, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->Move(Right, deltaTime);
    }

    //Mouse Input
    if(!cursorEnabled) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        camera->Rotate((float) mouseX, (float) mouseY);
    }
}

void update() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    projection = camera->projection(windowWidth, windowHeight);
}

void tick(){
    glfwSwapBuffers(window);
    glfwPollEvents();
}


//Callbacks
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    GLErrorManager(glViewport(0, 0, width, height));
    windowWidth = width;
    windowHeight = height;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }
}
