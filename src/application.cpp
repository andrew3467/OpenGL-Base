//
// Created by Andrew Graser on 3/12/2023.
//

#include "application.h"

Application::Application(int w, int h, const char* t) : width(w), height(h), title(t), shader(nullptr) {
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
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
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
    shader = new Shader("../../src/shaders/lit_cube.vert", "../../src/shaders/lit_cube.frag");
    lightShader = new Shader("../../src/shaders/light.vert", "../../src/shaders/light.frag");

    diffuseTex = new Texture2D("../../resources/textures/container2.png");
    specularTex = new Texture2D("../../resources/textures/container2_specular.png");

    camera = new Camera(width, height);
}


void Application::Run() {
    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



    //Vertex Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(0);

    //Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    //TexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);


    //Light VAO
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(0);


    //Disable cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glViewport(0, 0, width, height);
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
        camera->move(Forward, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->move(Backward, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->move(Left, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->move(Right, deltaTime);
    }

    //Mouse Input
    if(!cursorEnabled) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        camera->rotate((float) mouseX, (float) mouseY);
    }
}

void Application::render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    shader->bind();
    diffuseTex->bind(0);
    specularTex->bind(1);


    shader->setMat4("proj", camera->projection(width, height));
    shader->setMat4("view", camera->view());

    glBindVertexArray(VAO);
    for (int i = 0; i < 1; ++i) {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, cubePositions[i]);
        float angle = 20.0f * i;
        transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.3f, 1.0f, 0.5f));
        shader->setMat4("model", transform);


        shader->setVec3("viewPos", camera->position());

        shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        shader->setFloat("material.shininess", 32.0f);


        // light properties
        shader->setVec3("light.position", 1.2f, 1.0f, 2.0f);

        shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        shader->setVec3("light.specular", 0.0f, 0.0f, 0.0f);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    specularTex->unbind();
    diffuseTex->unbind();
    shader->unbind();

    //draw lights
    lightShader->bind();

    lightShader->setMat4("proj", camera->projection(width, height));
    lightShader->setMat4("view", camera->view());

    //Draw Lights
    glBindVertexArray(lightVAO);

    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(1.2f, 1.0f, 2.0f));
    transform = glm::scale(transform, glm::vec3(0.5f));

    lightShader->setMat4("model", transform);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    lightShader->unbind();
}

void Application::update() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;


    lightPosition += glm::vec3(-std::cos(glfwGetTime()) * 0.1f, 0, -std::sin(glfwGetTime()) * 0.1f);
}

void Application::tick(){
    glfwSwapBuffers(window);
    glfwPollEvents();
}


//Callbacks
void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }
}


//Cleanup
Application::~Application() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();
}


