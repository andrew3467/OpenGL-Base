//
// Created by Andrew Graser on 4/11/2023.
//

#ifndef OPENGL_BASE_TESTTEXTUREMAPPING_H
#define OPENGL_BASE_TESTTEXTUREMAPPING_H

#include "Test.h"
#include "renderer/Renderer.h"
#include "renderer/Texture2D.h"
#include "engine/Camera.h"

namespace test {
    class TestTextureMapping : public Test {
    public:
        TestTextureMapping();
        ~TestTextureMapping() override;

        void OnUpdate(float deltaTime, void* window) override;
        void OnRender(glm::vec2 windowSize) override;
        void OnImGuiRender() override;

    private:
        bool cursorEnabled;

        std::unique_ptr<Camera> camera;

        std::unique_ptr<VertexArray> cubeVA;
        std::unique_ptr<VertexBuffer> cubeVB;

        std::unique_ptr<VertexArray> lightVA;
        std::unique_ptr<VertexBuffer> lightVB;
        std::unique_ptr<IndexBuffer> lightIB;

        std::unique_ptr<Shader> shader;
        std::unique_ptr<Shader> solidShader;
        std::unique_ptr<Texture2D> tex;

        std::vector<glm::vec3> lightPositions;
        std::vector<glm::vec3> lightColors;
    };
}


#endif //OPENGL_BASE_TESTTEXTUREMAPPING_H
