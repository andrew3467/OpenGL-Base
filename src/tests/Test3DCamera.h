//
// Created by Andrew Graser on 4/7/2023.
//

#ifndef OPENGL_BASE_TEST3DCAMERA_H
#define OPENGL_BASE_TEST3DCAMERA_H

#include "Test.h"
#include "renderer/VertexArray.h"
#include "renderer/Renderer.h"
#include "renderer/Texture2D.h"
#include "engine/Camera.h"


namespace test{
    class Test3DCamera : public Test {
    public:
        Test3DCamera();
        ~Test3DCamera();

        void OnUpdate(float deltaTime, void* window) override;
        void OnRender(glm::vec2 windowSize) override;
        void OnImGuiRender() override;

    private:
        bool cursorEnabled;

        Renderer renderer;

        std::unique_ptr<VertexArray> cubeVA;
        std::unique_ptr<VertexBuffer> cubeVB;
        std::unique_ptr<IndexBuffer> cubeIB;

        std::unique_ptr<VertexArray> planeVA;
        std::unique_ptr<VertexBuffer> planeVB;
        std::unique_ptr<IndexBuffer> planeIB;

        std::unique_ptr<Shader> shader;

        glm::vec3 cubeColor;
        glm::vec3 cubeRotationAxis;
        float cubeRotationAngle;

        glm::vec3 planeScale;
        glm::vec3 planeColor;
    };
}

#endif //OPENGL_BASE_TEST3DCAMERA_H
