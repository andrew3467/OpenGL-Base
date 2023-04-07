//
// Created by Andrew Graser on 4/7/2023.
//

#include "Test3DCamera.h"
#include "renderer/VertexBufferLayout.h"
#include "GLFW/glfw3.h"
#include "imgui.h"


namespace test{

    Test3DCamera::Test3DCamera() : cubeColor(1.0f, 0.0f, 1.0f, 1.0f) {
        float vertices[] = {
                -1.0f,1.0f,0.0f,
                -1.0f,-1.0f,0.0f,
                1.0f,1.0f,0.0f,
                1.0f,-1.0f,0.0f,
                -1.0f,1.0f,-1.0f,
                -1.0f,-1.0f,-1.0f,
                1.0f,1.0f,-1.0f,
                1.0f,-1.0f,-1.0f
        };

        unsigned int indices[] = {
                0, 2, 3, 0, 3, 1,
                2, 6, 7, 2, 7, 3,
                6, 4, 5, 6, 5, 7,
                4, 0, 1, 4, 1, 5,
                0, 4, 6, 0, 6, 2,
                1, 5, 7, 1, 7, 3,
        };

        va = std::make_unique<VertexArray>();
        vb = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);
        va->AddBuffer(*vb, layout);

        ib = std::make_unique<IndexBuffer>(indices, 6);

        shader = std::make_unique<Shader>("../../src/shaders/SolidLit.vert", "../../src/shaders/SolidLit.frag");

        camera = std::make_unique<Camera>(glm::vec3(0.0f), 1280, 720);
    }

    Test3DCamera::~Test3DCamera() {

    }

    void Test3DCamera::OnUpdate(float deltaTime, void* window) {
        GLFWwindow* w = (GLFWwindow*)window;

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
        double mouseX, mouseY;
        glfwGetCursorPos(w, &mouseX, &mouseY);
        camera->Rotate((float) mouseX, (float) mouseY);

        Test::OnUpdate(deltaTime, window);
    }

    void Test3DCamera::OnRender() {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        glm::mat4 proj = camera->projection();
        glm::mat4 view = camera->view();

        {
            glm::mat4 transform = glm::mat4(1.0f);
            shader->Bind();
            shader->SetMat4("model", transform);
            shader->setVec4("color", 1.0f, 1.0f, 1.0f, 1.0f);

            renderer.Draw(*shader, *va, *ib);
        }

        Test::OnRender();
    }

    void Test3DCamera::OnImGuiRender() {
        ImGui::SliderFloat4("Cube Color", &cubeColor.x, 0.0f, 1.0f);


        Test::OnImGuiRender();
    }
}
