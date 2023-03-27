//
// Created by Andrew Graser on 3/12/2023.
//

#include "application.h"

#include <glPrimitives.h>

Application::Application(int w, int h, const char* t) : width(w), height(h), title(t){
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
    lightingShader = new Shader("../../src/shaders/texturedLit.vert", "../../src/shaders/texturedLit.frag");
    lightShader = new Shader("../../src/shaders/light.vert", "../../src/shaders/light.frag");
    skyboxShader = new Shader("../../src/shaders/skybox.vert", "../../src/shaders/skybox.frag");

    camera = new Camera(cameraPosition, width, height);

    skyboxTex = new Texture3D(faces);

    floorTex = new Texture2D("../../resources/textures/wood.png");
}


void Application::Run() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);

    unsigned int skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);



    transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(1.0f));
    transform = glm::translate(transform, glm::vec3(0.0f, 2.0f, 0.0f));


    //Disable cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glViewport(0, 0, width, height);
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << err << std::endl;
        }



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
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    lightingShader->bind();
    floorTex->bind();

    lightingShader->setMat4("proj", projection);
    lightingShader->setMat4("view", camera->view());

    lightingShader->setInt("texture_diffuse0", 0);

    lightingShader->setVec3("viewPos", camera->position());

    lightingShader->setInt("numPointLights", pointLights.size());
    for (unsigned int i = 0; i < pointLights.size(); ++i){
        lightingShader->setPointLight(pointLights[i], std::to_string(i));
    }

    lightingShader->setVec3("lightPos", lightPos);


    glPrimitive::drawPlane(lightingShader, glm::vec3(0.0, 0.0, 0.0),
                           glm::vec3(5.0f, 1.0f, 5.0f));


    floorTex->unbind();
    lightingShader->unbind();

    //Draw lights
    lightShader->bind();

    lightShader->setMat4("proj", projection);
    lightShader->setMat4("view", camera->view());

    glBindVertexArray(skyboxVAO);
    for (unsigned int i = 0; i < pointLights.size(); ++i) {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, pointLights[i].position);

        lightShader->setMat4("model", transform);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);

    lightShader->unbind();



    // draw skybox as last
    glDepthFunc(GL_LEQUAL);
    //glDepthMask(GL_FALSE);
    skyboxShader->bind();
    glm::mat4 view = glm::mat4(glm::mat3(camera->view())); // remove translation from the view matrix
    skyboxShader->setMat4("view", view);
    skyboxShader->setMat4("projection", projection);
    // skybox cube
    glBindVertexArray(skyboxVAO);
    skyboxTex->bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    //glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

    skyboxTex->unbind();
    skyboxShader->unbind();
}

void Application::update() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    projection = camera->projection(width, height);
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
    glDeleteVertexArrays(1, &skyboxVAO);

    glfwDestroyWindow(window);
    glfwTerminate();
}


