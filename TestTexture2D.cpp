//
// Created by Andrew Graser on 4/6/2023.
//

#include "TestTexture2D.h"
#include "engine/ErrorManager.h"
#include "renderer/VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"



#include <imgui.h>

namespace test{

    TestTexture2D::TestTexture2D() : m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0) {
        float positions[20] = {
                -50.0f, -50.0f, 0.0f, 0.0f, 0.0f,
                50.0f, -50.0f, 0.0f, 1.0f, 0.0f,
                50.0f, 50.0f, 0.0f, 1.0f, 1.0f,
                -50.0f, 50.0f, 0.0f, 0.0f, 1.0f,
        };

        unsigned int indices[6] = {
                0, 1, 2,
                2, 3, 0
        };

        GLErrorManager(glEnable(GL_BLEND));
        GLErrorManager(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        va = std::make_unique<VertexArray>();
        VertexBuffer vb(positions, sizeof(positions));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va->AddBuffer(vb, layout);

        ib = std::make_unique<IndexBuffer>(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0 ,0));

        tex = std::make_unique<Texture2D>("../../resources/textures/brick.png");
        shader = std::make_unique<Shader>("../../src/shader/TexturedUnlit.vert", "../../src/shader/TexturedUnlit.frag");

        shader->Bind();
        shader->SetMat4("proj", proj);
        shader->SetMat4("view", view);
    }

    TestTexture2D::~TestTexture2D() {

    }

    void TestTexture2D::OnUpdate(float deltaTime) {
        Test::OnUpdate(deltaTime);
    }

    void TestTexture2D::OnRender() {
        GLErrorManager(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLErrorManager(glClear(GL_COLOR_BUFFER_BIT));

        tex->Bind();
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            shader->Bind();
            shader->SetMat4("model", model);
            renderer.Draw(*shader, *va, *ib);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            shader->Bind();
            shader->SetMat4("model", model);
            renderer.Draw(*shader, *va, *ib);
        }

        Test::OnRender();
    }

    void TestTexture2D::OnImGuiRender() {
        ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        Test::OnImGuiRender();
    }
}
