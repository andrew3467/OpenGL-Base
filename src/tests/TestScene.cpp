//
// Created by Andrew Graser on 4/24/2023.
//

#include "TestScene.h"
#include "imgui.h"
#include "renderer/Renderer.h"

namespace test {
    TestScene::TestScene() {
        //Shaders
        modelShader = std::make_unique<Shader>("../../src/shaders/TexturedLit.vert", "../../src/shaders/TexturedLit.frag");
        solidShader = std::make_unique<Shader>("../../src/shaders/SolidLit.vert", "../../src/shaders/SolidLit.frag");

        camera = std::make_unique<Camera>(glm::vec3(0.0f, -2.0f, 0.0f), 1280, 720);


        trainModel = std::make_unique<Model>("lowpoly-steam-locomotive/Train.obj");
    }

    TestScene::~TestScene() {

    }

    void TestScene::OnUpdate(float deltaTime, void *window) {
        Test::OnUpdate(deltaTime, window);
    }

    void TestScene::OnRender(glm::vec2 windowSize) {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        {
            modelShader->Bind();

            modelShader->SetMat4("proj", camera->projection());
            modelShader->SetMat4("view", camera->view());
            modelShader->SetMat4("model", glm::mat4(1.0f));

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
                Renderer::DrawCube(*solidShader);
            }
        }

        Test::OnRender(windowSize);
    }

    void TestScene::OnImGuiRender() {
        if(ImGui::CollapsingHeader("Light Settings")){
            ImGui::Indent();
            if (ImGui::Button("Create Light")) {
                lightPositions.emplace_back(0.0f, 1.0f, 0.0f);
                lightColors.emplace_back(1.0f, 1.0f, 1.0f);
            }

            for (int i = 0; i < lightPositions.size(); i++) {
                if (ImGui::CollapsingHeader(("Light #" + std::to_string(i)).c_str())) {
                    ImGui::Indent();
                    ImGui::SliderFloat3("Position", &lightPositions[i].x, -10.0f, 10.0f);
                    ImGui::SliderFloat3("Color", &lightColors[i].x, 0.0f, 1.0f);
                }
            }
        }

        Test::OnImGuiRender();
    }
}
