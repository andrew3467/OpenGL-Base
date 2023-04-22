//
// Created by Andrew Graser on 4/11/2023.
//

#ifndef OPENGL_BASE_TESTMODELLOADING_H
#define OPENGL_BASE_TESTMODELLOADING_H

#include "Test.h"
#include "renderer/Renderer.h"
#include "engine/Camera.h"
#include "renderer/Texture2D.h"
#include "engine/Model.h"

namespace test {
    class TestModelLoading : public Test {
    public:
        TestModelLoading();
        ~TestModelLoading() override;

        void OnUpdate(float deltaTime, void *window) override;
        void OnRender(glm::vec2 windowSize) override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<Model> trainModel;

        std::unique_ptr<Shader> modelShader;
        std::unique_ptr<Shader> solidShader;

        std::unique_ptr<VertexArray> lightVA;
        std::unique_ptr<VertexBuffer> lightVB;
        std::unique_ptr<IndexBuffer> lightIB;

        std::vector<glm::vec3> lightPositions;
        std::vector<glm::vec3> lightColors;
    };
}


#endif //OPENGL_BASE_TESTMODELLOADING_H
