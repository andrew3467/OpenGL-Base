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
    shader = new Shader("../../src/shaders/default.vert", "../../src/shaders/default.frag");
    //shader = new Shader("../../src/shaders/lit_cube.vert", "../../src/shaders/lit_cube.frag");
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



    glBindVertexArray(VAO);
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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
    for (int i = 0; i < 10; ++i) {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, cubePositions[i]);
        float angle = 20.0f * i;
        transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.3f, 1.0f, 0.5f));
        shader->setMat4("model", transform);


        shader->setVec3("viewPos", camera->position());

        shader->setInt("material.diffuse", 0);
        shader->setInt("material.specular", 1);
        shader->setFloat("material.shininess", 32.0f);


        //Directional light properties
        shader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);

        shader->setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
        shader->setVec3("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
        shader->setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);

        shader->setInt("pointLightCount", 4);
        // point light 1
        for(int i = 0; i < 4; ++i){
            std::string index = std::to_string(i);
            shader->setVec3(("pointLights[" + index + "].position"), pointLightPositions[0]);
            shader->setVec3(("pointLights[" + index + "].ambient"), 0.05f, 0.05f, 0.05f);
            shader->setVec3(("pointLights[" + index + "].diffuse"), 0.8f, 0.8f, 0.8f);
            shader->setVec3(("pointLights[" + index + "].specular"), 1.0f, 1.0f, 1.0f);
            shader->setFloat(("pointLights[" + index + "].constant"), 1.0f);
            shader->setFloat(("pointLights[" + index + "].linear"), 0.09f);
            shader->setFloat(("pointLights[" + index + "].quadratic"), 0.032f);
        }

        // spotLight
        shader->setVec3("spotLight.position", camera->position());
        shader->setVec3("spotLight.direction", camera->front());
        shader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        shader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        shader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        shader->setFloat("spotLight.constant", 1.0f);
        shader->setFloat("spotLight.linear", 0.09f);
        shader->setFloat("spotLight.quadratic", 0.032f);
        shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


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

    for (int i = 0; i < 4; ++i) {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, pointLightPositions[i]);
        transform = glm::scale(transform, glm::vec3(0.5f));

        lightShader->setMat4("model", transform);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }


    lightShader->unbind();
}

void Application::update() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;


    pointLightPositions[0] += glm::vec3(-std::cos(glfwGetTime()) * 0.1f, 0, -std::sin(glfwGetTime()) * 0.1f);
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


