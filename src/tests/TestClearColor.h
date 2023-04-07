//
// Created by Andrew Graser on 4/6/2023.
//

#ifndef OPENGL_BASE_TESTCLEARCOLOR_H
#define OPENGL_BASE_TESTCLEARCOLOR_H

#include "Test.h"
#include "TestTexture2D.h"

namespace test{
    class TestClearColor : public Test  {
    public:
        TestClearColor();
        ~TestClearColor();

        void OnRender();
        void OnImGuiRender();

    private:
        float m_ClearColor[4];
    };
}

#endif //OPENGL_BASE_TESTCLEARCOLOR_H
