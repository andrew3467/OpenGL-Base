//
// Created by Andrew Graser on 4/17/2023.
//

#ifndef OPENGL_BASE_TESTPBR_H
#define OPENGL_BASE_TESTPBR_H

#include "Test.h"
#include "engine/Camera.h"
#include "engine/Model.h"
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"

namespace test {
    class TestPBR : public Test {
    public:
        TestPBR();
        ~TestPBR() override;

        void OnUpdate(float deltaTime, void *window) override;
        void OnRender(glm::vec2 windowSize) override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<Model> helmetModel;

        std::unique_ptr<Shader> modelShader;
        std::unique_ptr<Shader> solidShader;

        std::unique_ptr<VertexArray> cubeVA;
        std::unique_ptr<VertexBuffer> cubeVB;
        std::unique_ptr<IndexBuffer> cubeIB;

        std::vector<glm::vec3> lightPositions;
        std::vector<glm::vec3> lightColors;
    };
}


#endif //OPENGL_BASE_TESTPBR_H
