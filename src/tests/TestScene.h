//
// Created by Andrew Graser on 4/24/2023.
//

#ifndef OPENGL_BASE_TESTSCENE_H
#define OPENGL_BASE_TESTSCENE_H


#include "renderer/Shader.h"
#include "Test.h"
#include "engine/Model.h"

namespace test {
    class TestScene : public Test {
    public:
        TestScene();
        ~TestScene() override;

        void OnUpdate(float deltaTime, void *window) override;
        void OnRender(glm::vec2 windowSize) override;
        void OnImGuiRender() override;

    private:
        bool useGamma = false;

        std::unique_ptr<Shader> modelShader;
        std::unique_ptr<Shader> solidShader;

        std::unique_ptr<Model> trainModel;

        //Smoke Particles
        glm::vec3 smokePos = {0.0f, 0.0f, 0.0f};

        std::vector<glm::vec3> lightPositions = {
                {-2.0f, 1.0f, -2.0f},
                {-2.0f, 1.0f, 2.0f},
                {2.0f, 1.0f, -2.0f},
                {2.0f, 1.0f, 2.0f},
        };
        std::vector<glm::vec3> lightColors = {
                {1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f},
        };
    };
}


#endif //OPENGL_BASE_TESTSCENE_H
