//
// Created by Andrew Graser on 4/6/2023.
//

#include "Test.h"
#include "imgui.h"

#include <engine/ErrorManager.h>
#include "GLFW/glfw3.h"

namespace test{

    TestMenu::TestMenu(Test *&currentTestPointer) : m_CurrentTest(currentTestPointer) {

    }

    void TestMenu::OnImGuiRender() {
        for(auto& test : m_Tests){
            if(ImGui::Button(test.first.c_str())){
                m_CurrentTest = test.second();
            }
        }
    }

    void Test::OnImGuiRender() {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
    }

    void Test::OnRender(glm::vec2 windowSize) {
        glViewport(0, 0, windowSize.x, windowSize.y);
    }

    void Test::OnUpdate(float deltaTime, void *window) {
        if(camera != nullptr) {
            GLFWwindow *w = (GLFWwindow *) window;

            //Camera Input
            if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
                camera->Move(Forward, deltaTime);
            }
            if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {
                camera->Move(Backward, deltaTime);
            }
            if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) {
                camera->Move(Left, deltaTime);
            }
            if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) {
                camera->Move(Right, deltaTime);
            }

            //Mouse Input
            if (glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_MIDDLE)) {
                double mouseX, mouseY;
                glfwGetCursorPos(w, &mouseX, &mouseY);
                camera->Rotate((float) mouseX, (float) mouseY);
            }
        }
    }
}
