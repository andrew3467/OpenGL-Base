//
// Created by Andrew Graser on 3/12/2023.
//

#ifndef OPENGL_BASE_APPLICATION_H
#define OPENGL_BASE_APPLICATION_H

#include <string>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "texture2d.h"


class Application{
public:
    Application(int w, int h, const char* t);

    ~Application();


private:
    unsigned int VAO, VBO, EBO;
    int width, height;
    const char* title;

    GLFWwindow* window;

    Shader* shader;
    Texture2D* texture;

    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 transform;


    unsigned int indices[36] = {
            0, 1, 2,
            2, 3, 0
    };

    //Position, TexCoord
    const float vertices[40] = {
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,      //0
            0.5f, -0.5f, 0.f,       1.0f, 0.0f,      //1
            0.5f, 0.5f, 0.0f,    1.0f, 1.0f,  //2
            -0.5f, 0.5f, 0.f,    0.0f, 0.0f,  //3
    };


public:
    void Run();

private:
    //initialization
    void initGlFW();
    static void initGLAD();
    void initObjects();

    void render();
    void tick();

    //Callbacks
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif //OPENGL_BASE_APPLICATION_H
