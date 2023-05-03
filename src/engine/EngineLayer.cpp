//
// Created by apgra on 5/3/2023.
//

#include "EngineLayer.h"
#include "GLFW/glfw3.h"

void EngineLayer::Tick(GLFWwindow* window) {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
