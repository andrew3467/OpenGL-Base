//
// Created by Andrew Graser on 4/18/2023.
//

#ifndef OPENGL_BASE_TESTPARTICLES_H
#define OPENGL_BASE_TESTPARTICLES_H

#include "Test.h"
#include "renderer/Shader.h"
#include "engine/Camera.h"
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Texture2D.h"
#include "engine/ParticleEmitter.h"

namespace test {
    class TestParticles : public Test {
    public:
        TestParticles();
        ~TestParticles() override;

        void OnUpdate(float deltaTime, void *window) override;
        void OnRender(glm::vec2 windowSize) override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<ParticleEmitter> particleEmitter;
        ParticleProps particleConfig;
    };
}


#endif //OPENGL_BASE_TESTPARTICLES_H
