//
// Created by Andrew Graser on 4/18/2023.
//

#include "TestParticles.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/Renderer.h"
#include <imgui.h>

#define NUM_PARTICLES 500

namespace test {
    TestParticles::TestParticles() {
        particleEmitter = std::make_unique<ParticleEmitter>("../../resources/textures/fire.png");

        camera = std::make_unique<Camera>(glm::vec3(0.0f, -2.0f, 0.0f), 1280, 720);

        //Init Config
        particleConfig.ColorBegin = {254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f};
        particleConfig.ColorEnd = {254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f};
        particleConfig.SizeBegin = 0.5f, particleConfig.SizeVariation = 0.3f, particleConfig.SizeEnd = 0.0f;
        particleConfig.LifeTime = 1.0f;
        particleConfig.Velocity = {0.0f, 0.0f, 0.0f};
        particleConfig.VelocityVariation = {3.0f, 1.0f, 3.0f};
        particleConfig.Position = {0.0f, 0.0f, 0.0f};

        //Alpha transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    TestParticles::~TestParticles() {

    }

    void TestParticles::OnUpdate(float deltaTime, void *window) {
        particleEmitter->UpdateParticles(deltaTime);
        particleEmitter->Emit(particleConfig);

        Test::OnUpdate(deltaTime, window);
    }

    void TestParticles::OnRender(glm::vec2 windowSize) {
        //glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        particleEmitter->Draw(camera->viewProjection());

        Test::OnRender(windowSize);
    }

    void TestParticles::OnImGuiRender() {
        ImGui::SliderFloat3("ColorBegin", &particleConfig.ColorBegin.x, 0.0f, 1.0f);
        ImGui::SliderFloat3("ColorEnd", &particleConfig.ColorEnd.x, 0.0f, 1.0f);

        Test::OnImGuiRender();
    }
}
