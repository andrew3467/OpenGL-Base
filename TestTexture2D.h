//
// Created by Andrew Graser on 4/6/2023.
//

#ifndef OPENGL_BASE_TESTCLEARCOLOR_H
#define OPENGL_BASE_TESTCLEARCOLOR_H

#include "Test.h"
#include "renderer/VertexArray.h"

#include "renderer/Shader.h"
#include "renderer/Texture2D.h"
#include "renderer/Renderer.h"

namespace test {
    class TestTexture2D : public Test  {
    public:
        TestTexture2D();
        ~TestTexture2D() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender();

    private:
        Renderer renderer;

        std::unique_ptr<VertexArray> va;
        std::unique_ptr<IndexBuffer> ib;

        std::unique_ptr<Shader> shader;
        std::unique_ptr<Texture2D> tex;

        glm::vec3 m_TranslationA;
        glm::vec3 m_TranslationB;
    };
}

#endif //OPENGL_BASE_TESTCLEARCOLOR_H
