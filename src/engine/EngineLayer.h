//
// Created by apgra on 5/3/2023.
//

#ifndef OPENGL_BASE_ENGINELAYER_H
#define OPENGL_BASE_ENGINELAYER_H

//std
#include <memory>

#include "Camera.h"

class GLFWwindow;

class EngineLayer {
public:
    EngineLayer(){}
    virtual ~EngineLayer(){}

    virtual void OnUpdate(float deltaTime, void* window){}
    virtual void OnRender(){}
    virtual void OnImGuiRender(){}

    void Tick(GLFWwindow* window);

private:
    std::unique_ptr<Camera> m_Camera;
};


#endif //OPENGL_BASE_ENGINELAYER_H
