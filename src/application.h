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

    //Position, TexCoord
    const float vertices[40] = {
            -1, -1,  1,     0.0f, 0.0f, //0
            1, -1,  1,      1.0f, 0.0f,  //1
            -1,  1,  1,  0.0f, 1.0f, //2
            1,  1,  1,   1.0f, 1.0f,//3
            -1, -1, -1,  0.0f, 0.0f,//4
            1, -1, -1,   0.0f, 1.0f,//5
            -1,  1, -1,  0.0f, 1.0f,//6
            1,  1, -1,   1.0f, 1.0f//7
    };

    unsigned int indices[36] = {
            //Top
            2, 6, 7,
            2, 3, 7,

            //Bottom
            0, 4, 5,
            0, 1, 5,

            //Left
            0, 2, 6,
            0, 4, 6,

            //Right
            1, 3, 7,
            1, 5, 7,

            //Front
            0, 2, 3,
            0, 1, 3,

            //Back
            4, 6, 7,
            4, 5, 7
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
