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
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        Renderer renderer;

        std::unique_ptr<Camera> camera;

        std::unique_ptr<VertexArray> va;
        std::unique_ptr<VertexBuffer> vb;
        std::unique_ptr<IndexBuffer> ib;

        std::unique_ptr<Shader> shader;
        std::unique_ptr<Texture2D> tex;

        glm::vec4 cubeColor;
    };
}

#endif //OPENGL_BASE_TEST3DCAMERA_H
