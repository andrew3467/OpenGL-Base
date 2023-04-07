//
// Created by Andrew Graser on 4/6/2023.
//

#include "TestClearColor.h"
#include "engine/ErrorManager.h"

#include <imgui.h>

namespace test{

    TestClearColor::TestClearColor() : m_ClearColor {0.2f, 0.3f, 0.8f, 1.0f} {

    }

    TestClearColor::~TestClearColor() {

    }

    void TestClearColor::OnRender() {
        GLErrorManager(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
        GLErrorManager(glClear(GL_COLOR_BUFFER_BIT));

        Test::OnRender();
    }

    void TestClearColor::OnImGuiRender() {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);

        Test::OnImGuiRender();
    }
}
