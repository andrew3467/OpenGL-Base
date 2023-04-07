#include "engine/ErrorManager.h"
#include "GLFW/glfw3.h"


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

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"


#include <iostream>


int windowWidth = 1280;
int windowHeight = 720;
const char* windowTitle = "OpenGL Base";
GLFWwindow* window;

Renderer renderer;

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

    Texture3D skyboxTex(faces);
    Texture2D woodTex("../../resources/textures/wood.png");
    Texture2D brickTex("../../resources/textures/brick.png");

    Shader lightingShader("../../src/shaders/texturedLit.vert", "../../src/shaders/texturedLit.frag");
    Shader colorShader("../../src/shaders/solidColor.vert", "../../src/shaders/solidColor.frag");
    Shader skyboxShader("../../src/shaders/skybox.vert", "../../src/shaders/skybox.frag");



    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    const char* glsl_version = "#version 460";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestTexture2D>("2D Texture");


    //Disable cursor
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLErrorManager(glViewport(0, 0, windowWidth, windowHeight));

    while(!glfwWindowShouldClose(window)) {
        processInput(window);


        renderer.Clear();
        GLErrorManager(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));


        //Draw ImGui Windows
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if(currentTest){
            currentTest->OnUpdate(deltaTime);
            currentTest->OnRender();

            ImGui::Begin("test");

            if(currentTest != testMenu && ImGui::Button("<-")){
                delete currentTest;
                currentTest = testMenu;
            }

            currentTest->OnImGuiRender();

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        tick();
    }


    if(currentTest != testMenu){
        delete testMenu;
    }
    delete currentTest;


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
