//
// Created by apgra on 4/9/2023.
//

#ifndef OPENGL_BASE_TESTLIGHTING_H
#define OPENGL_BASE_TESTLIGHTING_H

#include "Test.h"
#include "renderer/VertexArray.h"
#include "renderer/Renderer.h"
#include "renderer/Texture2D.h"
#include "engine/Camera.h"
#include "../engine/Lights.h"

//STD
#include <vector>

namespace test {
    class TestLighting : public Test {
    public:
        TestLighting();
        ~TestLighting();

        void OnUpdate(float deltaTime, void* window) override;
        void OnRender(glm::vec2 windowSize) override;
        void OnImGuiRender() override;

    private:
        bool cursorEnabled;

        std::vector<PointLight> lights;

        Renderer renderer;

        std::unique_ptr<Camera> camera;

        std::unique_ptr<VertexArray> planeVA;
        std::unique_ptr<VertexBuffer> planeVB;

        std::unique_ptr<VertexArray> cubeVA;
        std::unique_ptr<VertexBuffer> cubeVB;
        std::unique_ptr<IndexBuffer> cubeIB;

        std::unique_ptr<Shader> shader;
        std::unique_ptr<Shader> lightShader;
        std::unique_ptr<Texture2D> tex;

        std::vector<glm::vec3> lightPositions;
        std::vector<glm::vec3> lightColors;
    };
}


#endif //OPENGL_BASE_TESTLIGHTING_H
