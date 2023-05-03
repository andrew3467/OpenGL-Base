//
// Created by apgra on 5/3/2023.
//

#ifndef OPENGL_BASE_SANDBOXLAYER_H
#define OPENGL_BASE_SANDBOXLAYER_H


#include "engine/EngineLayer.h"

class SandboxLayer : public EngineLayer {
public:
    SandboxLayer();
    ~SandboxLayer() override;

private:

public:
    void OnUpdate(float deltaTime, void* window) override;
    void OnRender() override;
    void OnImGuiRender() override;
};


#endif //OPENGL_BASE_SANDBOXLAYER_H
