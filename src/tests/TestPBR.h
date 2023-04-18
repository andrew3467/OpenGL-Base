//
// Created by Andrew Graser on 4/17/2023.
//

#ifndef OPENGL_BASE_TESTPBR_H
#define OPENGL_BASE_TESTPBR_H

#include "Test.h"
#include "engine/Camera.h"
#include "engine/Model.h"

namespace test {
    class TestPBR : public Test {
    public:
        TestPBR();
        ~TestPBR() override;

        void OnUpdate(float deltaTime, void *window) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<Camera> camera;

        std::unique_ptr<Model> helmetModel;

        std::unique_ptr<Shader> modelShader;
        std::unique_ptr<Shader> solidShader;

        std::unique_ptr<VertexArray> lightVA;
        std::unique_ptr<VertexBuffer> lightVB;
        std::unique_ptr<IndexBuffer> lightIB;

        std::vector<glm::vec3> lightPositions;
        std::vector<glm::vec3> lightColors;
    };
}


#endif //OPENGL_BASE_TESTPBR_H