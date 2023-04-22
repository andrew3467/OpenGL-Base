#include "engine/ErrorManager.h"
#include "GLFW/glfw3.h"

#include "renderer/VertexBufferLayout.h"
#include "renderer/Renderer.h"

#include "ObjectData.h"


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/Test3DCamera.h"
#include "tests/TestLighting.h"
#include "tests/TestTextureMapping.h"
#include "tests/TestModelLoading.h"
#include "tests/TestPBR.h"
#include "tests/TestInstancedRender.h"
#include "tests/TestParticles.h"


#include <iostream>


int windowWidth = 1280;
int windowHeight = 720;
const char* windowTitle = "OpenGL Base";
GLFWwindow* window;

Renderer renderer;

glm::mat4 projection;
glm::mat4 transform;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void initGlFW();
void initGLAD();

void processInput(GLFWwindow* window);

void update();
void tick();

//Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
    initGlFW();
    initGLAD();

    GLErrorManager(glEnable(GL_DEPTH_TEST));


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
    testMenu->RegisterTest<test::Test3DCamera>("3D Camera");
    testMenu->RegisterTest<test::TestLighting>("Lighting Test");
    testMenu->RegisterTest<test::TestTextureMapping>("Texture Mapping");
    testMenu->RegisterTest<test::TestModelLoading>("Model Loading");
    testMenu->RegisterTest<test::TestPBR>("PBR");
    testMenu->RegisterTest<test::TestInstancedRender>("Instanced Renderer");
    testMenu->RegisterTest<test::TestParticles>("Particles");


    //Disable cursor
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLErrorManager(glViewport(0, 0, windowWidth, windowHeight));

    try {
        while (!glfwWindowShouldClose(window)) {
            renderer.Clear();
            GLErrorManager(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));


            //Draw ImGui Windows
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currentTest) {
                currentTest->OnUpdate(deltaTime, window);
                currentTest->OnRender(glm::vec2(windowWidth, windowHeight));

                ImGui::Begin("test");

                if (currentTest != testMenu && ImGui::Button("<-")) {
                    delete currentTest;
                    currentTest = testMenu;
                }

                currentTest->OnImGuiRender();

                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            tick();
        }
    }
    catch (std::exception& e){
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
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

    return EXIT_SUCCESS;
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

void update() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
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
