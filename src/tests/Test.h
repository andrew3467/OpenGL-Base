//
// Created by Andrew Graser on 4/6/2023.
//

#ifndef OPENGL_BASE_TEST_H
#define OPENGL_BASE_TEST_H


#include <string>
#include <functional>
#include <iostream>

namespace test {
    class Test {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime, void* window){}
        virtual void OnRender();
        virtual void OnImGuiRender();
    };


    class TestMenu : public Test {
    public:
        TestMenu(Test*& currentTestPointer);
         ~TestMenu(){}

        void OnImGuiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name){
            std::cout << "Registering Test " << name << '\n';

            m_Tests.push_back(std::make_pair(name, [](){return new T;}));
        }

    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };
}


#endif //OPENGL_BASE_TEST_H
