//
// Created by Andrew Graser on 4/6/2023.
//

#include "Test.h"
#include "imgui.h"

#include <glad/glad.h>

namespace test{

    TestMenu::TestMenu(Test *&currentTestPointer) : m_CurrentTest(currentTestPointer) {

    }

    void TestMenu::OnImGuiRender() {
        for(auto& test : m_Tests){
            if(ImGui::Button(test.first.c_str())){
                m_CurrentTest = test.second();
            }
        }
    }

    void Test::OnImGuiRender() {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
    }

    void Test::OnRender() {
        glViewport(0, 0, 1280, 720);
    }
}
