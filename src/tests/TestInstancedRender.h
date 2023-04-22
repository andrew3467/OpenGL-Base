//
// Created by Andrew Graser on 4/18/2023.
//

#ifndef OPENGL_BASE_TESTINSTANCEDRENDER_H
#define OPENGL_BASE_TESTINSTANCEDRENDER_H

#include <tests/Test.h>
#include "engine/Camera.h"
#include "engine/Model.h"


namespace test {
    class TestInstancedRender : public Test {
    public:
        TestInstancedRender();

        ~TestInstancedRender() override;

        void OnUpdate(float deltaTime, void *window) override;

        void OnRender(glm::vec2 windowSize) override;

        void OnImGuiRender() override;

    private:
        std::vector<glm::vec3> positions;

        std::unique_ptr<Model> helmetModel;

        std::unique_ptr<Shader> modelShader;
        std::unique_ptr<Shader> solidShader;

        std::unique_ptr<VertexArray> cubeVA;
        std::unique_ptr<VertexBuffer> cubeVB;
        std::unique_ptr<VertexBuffer> instanceVB;
        std::unique_ptr<IndexBuffer> cubeIB;
    };
}


#endif //OPENGL_BASE_TESTINSTANCEDRENDER_H
