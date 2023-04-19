//
// Created by Andrew Graser on 4/7/2023.
//

#include "Test3DCamera.h"
#include "renderer/VertexBufferLayout.h"
#include "GLFW/glfw3.h"
#include "imgui.h"


namespace test{

    Test3DCamera::Test3DCamera() : cubeColor(1.0f, 1.0f, 0.0f), cubeRotationAxis(1.0f, 1.0f, 1.0f),
                                   cubeRotationAngle(0.0f), planeScale(1.0f, 1.0f, 1.0f),
                                   planeColor(0.7f, 0.2f, 0.5f)
    {
        float cubeVertices[24] = {
                -0.5, -0.5,  0.5, //0
                0.5, -0.5,  0.5, //1
                -0.5,  0.5,  0.5, //2
                0.5,  0.5,  0.5, //3
                -0.5, -0.5, -0.5, //4
                0.5, -0.5, -0.5, //5
                -0.5,  0.5, -0.5, //6
                0.5,  0.5, -0.5  //7
        };

        unsigned int cubeIndices[36] = {
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

        float planeVertices[12] = {
                -1.0f, 0.0f, -1.0f,
                1.0f, 0.0f, -1.0f,
                1.0f, 0.0f, 1.0f,
                -1.0f, 0.0f, 1.0f,
        };

        unsigned int planeIndices[6] = {
                0, 1, 2,
                2, 3, 0
        };

        {
            cubeVA = std::make_unique<VertexArray>();
            cubeVB = std::make_unique<VertexBuffer>(cubeVertices, sizeof(cubeVertices));

            VertexBufferLayout layout;
            layout.Push<float>(3);
            cubeVA->AddBuffer(*cubeVB, layout);

            cubeIB = std::make_unique<IndexBuffer>(cubeIndices, 36);
        }

        {
            planeVA = std::make_unique<VertexArray>();
            planeVB = std::make_unique<VertexBuffer>(planeVertices, sizeof(planeVertices));

            VertexBufferLayout layout;
            layout.Push<float>(3);
            planeVA->AddBuffer(*planeVB, layout);

            planeIB = std::make_unique<IndexBuffer>(planeIndices, 6);
        }

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
        if(!cursorEnabled) {
            double mouseX, mouseY;
            glfwGetCursorPos(w, &mouseX, &mouseY);
            camera->Rotate((float) mouseX, (float) mouseY);
        }


        if(glfwGetKey(w, GLFW_KEY_SPACE) == GLFW_PRESS){
            GLint toggle = cursorEnabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
            glfwSetInputMode(w, GLFW_CURSOR, toggle);
            cursorEnabled = !cursorEnabled;
        }

        Test::OnUpdate(deltaTime, window);
    }

    void Test3DCamera::OnRender(glm::vec2 windowSize) {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        glm::mat4 proj = camera->projection();
        glm::mat4 view = camera->view();

        shader->Bind();
        shader->SetMat4("proj", proj);
        shader->SetMat4("view", view);

        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
            transform = glm::rotate(transform, glm::radians(cubeRotationAngle), cubeRotationAxis);

            shader->Bind();
            shader->SetMat4("model", transform);
            shader->SetVec3("color", cubeColor);

            renderer.Draw(*shader, *cubeVA, *cubeIB);
        }
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));
            transform = glm::scale(transform, planeScale);

            shader->Bind();
            shader->SetMat4("model", transform);
            shader->SetVec3("color", planeColor);

            renderer.Draw(*shader, *planeVA, *planeIB);
        }

        Test::OnRender(windowSize);
    }

    void Test3DCamera::OnImGuiRender() {
        ImGui::SliderFloat3("Cube Color", &cubeColor.x, 0.0f, 1.0f);
        ImGui::SliderFloat3("Cube Rotation", &cubeRotationAxis.x, 0, 1);
        ImGui::SliderFloat("Rotation Angle", &cubeRotationAngle, 0.0f, 360.0f);

        ImGui::Spacing();

        ImGui::SliderFloat3("Plane Color", &planeColor.x, 0.0f, 1.0f);
        ImGui::SliderFloat3("Plane Scale", &planeScale.x, 0.0f, 20.0f);


        Test::OnImGuiRender();
    }
}
