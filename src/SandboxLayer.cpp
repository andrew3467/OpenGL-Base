//
// Created by apgra on 5/3/2023.
//

#include "SandboxLayer.h"

SandboxLayer::SandboxLayer() {

}

SandboxLayer::~SandboxLayer() {

}

void SandboxLayer::OnUpdate(float deltaTime, void *window) {
    EngineLayer::OnUpdate(deltaTime, window);
}

void SandboxLayer::OnRender() {
    EngineLayer::OnRender();
}

void SandboxLayer::OnImGuiRender() {
    EngineLayer::OnImGuiRender();
}
