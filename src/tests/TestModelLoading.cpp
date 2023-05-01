//
// Created by Andrew Graser on 4/11/2023.
//

#include "TestModelLoading.h"
#include "GLFW/glfw3.h"
#include "renderer/VertexBufferLayout.h"
#include "imgui.h"

namespace test {
    TestModelLoading::TestModelLoading() {
        float lightVertices[24] = {
                -0.5, -0.5,  0.5, //0
                0.5, -0.5,  0.5, //1
                -0.5,  0.5,  0.5, //2
                0.5,  0.5,  0.5, //3
                -0.5, -0.5, -0.5, //4
                0.5, -0.5, -0.5, //5
                -0.5,  0.5, -0.5, //6
                0.5,  0.5, -0.5  //7
        };

        unsigned int lightIndices[36] = {
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

        trainModel = std::make_unique<Model>("../../resources/models/lowpoly-steam-locomotive/Train.obj");

        {
            lightVA = std::make_unique<VertexArray>();
            lightVB = std::make_unique<VertexBuffer>(lightVertices, sizeof(lightVertices));

            VertexBufferLayout layout;
            layout.Push<float>(3);
            lightVA->AddBuffer(*lightVB, layout);

            lightIB = std::make_unique<IndexBuffer>(lightIndices, 36);
        }

        modelShader = std::make_unique<Shader>("../../src/shaders/TexturedLit.vert", "../../src/shaders/TexturedLit.frag");
        solidShader = std::make_unique<Shader>("../../src/shaders/SolidLit.vert", "../../src/shaders/SolidLit.frag");


        camera = std::make_unique<Camera>(glm::vec3(0.0f), 1280, 720);
    }

    TestModelLoading::~TestModelLoading() {

    }

    void TestModelLoading::OnUpdate(float deltaTime, void *window) {
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

        Test::OnUpdate(deltaTime, window);
    }

    void TestModelLoading::OnRender(glm::vec2 windowSize) {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        //Train
        {
            modelShader->Bind();

            modelShader->SetMat4("proj", camera->projection());
            modelShader->SetMat4("view", camera->view());
            modelShader->SetMat4("model", glm::mat4(1.0f));

            modelShader->SetInt("texture_diffuse0", 0);

            modelShader->SetVec3("viewPos", camera->position());

            modelShader->SetInt("numLights", lightPositions.size());
            modelShader->SetInt("gamma", false);
            for (int i = 0; i < lightPositions.size(); ++i) {
                std::string index = std::to_string(i);
                modelShader->SetVec3(("lightPositions[" + index + "]"), lightPositions[i]);
                modelShader->SetVec3(("lightColors[" + index + "]"), lightColors[i]);
            }

            trainModel->Draw(*modelShader);
        }


        //Lights
        {
            solidShader->Bind();
            solidShader->SetMat4("proj", camera->projection());
            solidShader->SetMat4("view", camera->view());

            for (unsigned int i = 0; i < lightPositions.size(); ++i) {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPositions[i]);
                model = glm::scale(model, glm::vec3(0.25f));

                solidShader->SetVec3("color", lightColors[i]);
                solidShader->SetMat4("model", model);
                Renderer::Draw(*solidShader, *lightVA, *lightIB);
            }

        }

        Test::OnRender(windowSize);
    }

    void TestModelLoading::OnImGuiRender() {
        if(ImGui::Button("Create Light")){
            lightPositions.emplace_back(0.0f, 1.0f, 0.0f);
            lightColors.emplace_back(0.1f, 0.1f, 0.1f);
        }

        for(int i = 0; i < lightPositions.size(); i++){
            if(ImGui::CollapsingHeader(("Light #" + std::to_string(i)).c_str())){
                ImGui::SliderFloat3("Position", &lightPositions[i].x, -10.0f, 10.0f);
                ImGui::SliderFloat3("Color", &lightColors[i].x, 0.0f, 1.0f);
            }
        }

        Test::OnImGuiRender();
    }
}