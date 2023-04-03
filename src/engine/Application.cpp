//
// Created by Andrew Graser on 3/12/2023.
//

#include "Application.h"

#include "engine/GLPrimitives.h"

Application::Application(int w, int h, const char* t) : windowWidth(w), windowHeight(h), windowTitle(t){
    initGlFW();
    initGLAD();
    initObjects();
}


//Initialization
void Application::initGlFW() {
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
    glfwSetFramebufferSizeCallback(window, Application::framebuffer_size_callback);
    glfwSetKeyCallback(window, Application::key_callback);
}

void Application::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD\n");
    }
}

void Application::initObjects() {
    lightingShader = Shader("../../src/shaders/texturedLit.vert", "../../src/shaders/texturedLit.frag");
    colorShader = Shader("../../src/shaders/solidColor.vert", "../../src/shaders/solidColor.frag");
    skyboxShader = Shader("../../src/shaders/skybox.vert", "../../src/shaders/skybox.frag");

    camera = new Camera(cameraPosition, windowWidth, windowHeight);

    skyboxTex = Texture3D(faces);
    floorTex = Texture2D("../../resources/textures/wood.png");
}


void Application::Run() {
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glEnable(GL_PROGRAM_POINT_SIZE));
    GLCall(glEnable(GL_FRAMEBUFFER_SRGB));

    skyboxVA = VertexArray();
    skyboxVB = VertexBuffer(skyboxVertices, sizeof(skyboxVertices));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    skyboxVA.AddBuffer(skyboxVB, layout);


    transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(1.0f));
    transform = glm::translate(transform, glm::vec3(0.0f, 2.0f, 0.0f));


    //Disable cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLCall(glViewport(0, 0, windowWidth, windowHeight));
    while(!glfwWindowShouldClose(window)){
        processInput(window);


        render();
        update();
        tick();
    }

}

void Application::processInput(GLFWwindow *window) {
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



void Application::render() {
    GLCall(glClearColor(0.05f, 0.05f, 0.05f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    //Floor
    lightingShader.Bind();
    floorTex.Bind();

    lightingShader.SetMat4("proj", projection);
    lightingShader.SetMat4("view", camera->view());

    lightingShader.SetInt("texture_diffuse0", 0);


    lightingShader.SetInt("numPointLights", numPointLights);
    for (unsigned int i = 0; i < numPointLights; ++i){
        lightingShader.SetPointLight(pointLights[i], std::to_string(i));
    }

    lightingShader.SetVec3("viewPos", camera->position());
    lightingShader.SetFloat("shininess", 128.0f);

    lightingShader.SetInt("blinn", false);
    lightingShader.SetInt("gamma", true);

    glPrimitive::DrawPlane(lightingShader, glm::vec3(0.0, 0.0, 0.0),
                           glm::vec3(20.0f, 1.0f, 20.0f));


    floorTex.Unbind();
    lightingShader.Unbind();

    //Draw lights
    colorShader.Bind();

    colorShader.SetMat4("proj", projection);
    colorShader.SetMat4("view", camera->view());

    for (unsigned int i = 0; i < numPointLights; ++i) {
        colorShader.SetVec3("color", pointLights[i].ambient);
        glPrimitive::DrawCube(colorShader, pointLights[i].position, glm::vec3(0.25f));
    }

    colorShader.Unbind();

    //Draw Cubes
    colorShader.Bind();

    colorShader.SetMat4("proj", projection);
    colorShader.SetMat4("view", camera->view());

    for(int i = 0; i < cubePositions.size(); i++){
        colorShader.SetVec3("color", 0.3f, 0.5f, 0.8f);
        glPrimitive::DrawCube(colorShader, cubePositions[i], glm::vec3(1.0f), cubeRotations[i], 30);
    }

    colorShader.Unbind();



    // draw skybox as last
    GLCall(glDepthFunc(GL_LEQUAL));
    //glDepthMask(GL_FALSE);
    skyboxShader.Bind();
    glm::mat4 view = glm::mat4(glm::mat3(camera->view())); // remove translation from the view matrix
    skyboxShader.SetMat4("view", view);
    skyboxShader.SetMat4("projection", projection);
    // skybox cube
    //skyboxVA->bind();
    skyboxTex.bind();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
    //skyboxVA->Unbind();
    //glDepthMask(GL_TRUE);
    GLCall(glDepthFunc(GL_LESS));

    skyboxTex.unbind();
    skyboxShader.Unbind();
}

void Application::update() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    projection = camera->projection(windowWidth, windowHeight);
}

void Application::tick(){
    glfwSwapBuffers(window);
    glfwPollEvents();
}


//Callbacks
void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    GLCall(glViewport(0, 0, width, height));
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }
}


//Cleanup
Application::~Application() {
    glfwDestroyWindow(window);
    glfwTerminate();
}


