//
// Created by Andrew Graser on 3/12/2023.
//

#ifndef OPENGL_BASE_APPLICATION_H
#define OPENGL_BASE_APPLICATION_H

#include <string>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader.h>
#include <texture2d.h>
#include <texture3d.h>
#include <camera.h>
#include <model.h>
#include <lights.h>


class Application{
public:
    Application(int w, int h, const char* t);

    ~Application();


private:
    unsigned int skyboxVAO;
    int width, height;
    const char* title;

    GLFWwindow* window;

    Shader* lightShader;
    Shader* lightingShader;
    Shader* skyboxShader;

    Texture3D* skyboxTex;
    Texture2D* floorTex;

    Camera* camera;
    glm::mat4 projection;

    Model* model;

    glm::mat4 transform;

    glm::vec3 lightColor = glm::vec3(1.0f);

    bool cursorEnabled = false;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    bool blinn = false;
    bool blinnKeyPressed = false;

    std::vector<std::string> faces =
    {
        "../../resources/textures/skybox/right.jpg",
        "../../resources/textures/skybox/left.jpg",
        "../../resources/textures/skybox/top.jpg",
        "../../resources/textures/skybox/bottom.jpg",
        "../../resources/textures/skybox/front.jpg",
        "../../resources/textures/skybox/back.jpg"
    };

    float skyboxVertices[108] = {
            // positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
    };

    glm::vec3 cameraPosition = glm::vec3(0.0f, 1.0f, -4.0f);
    glm::vec3 lightPos = glm::vec3(0.0f, 3.0f, 0.0f);

    int numPointLights = 4;
    std::vector<PointLight> pointLights = {
            PointLight(
                    glm::vec3(-3.0f, 0.0f, 0.0f),
                glm::vec3(0.25f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                0.0f,
                0.0f,
                0.0f
            ),
            PointLight(
                    glm::vec3(-1.0f, 0.0f, 0.0f),
                    glm::vec3(0.50f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    0.0f,
                    0.0f,
                    0.0f
            ),
            PointLight(
                    glm::vec3 (1.0f, 0.0f, 0.0f),
                    glm::vec3(0.75f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    0.0f,
                    0.0f,
                    0.0f
            ),
            PointLight(
                    glm::vec3 (1.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    0.0f,
                    0.0f,
                    0.0f
            )
    };


public:
    void Run();

private:
    //initialization
    void initGlFW();
    static void initGLAD();
    void initObjects();

    void processInput(GLFWwindow* window);

    void render();
    void update();
    void tick();

    //Callbacks
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif //OPENGL_BASE_APPLICATION_H
