//
// Created by Andrew Graser on 4/3/2023.
//
#include "Renderer.h"
#include "engine/ErrorManager.h"


void Renderer::Draw(const Shader& shader, const VertexArray &va, const IndexBuffer &ib, unsigned int numInstances) {
    shader.Bind();
    va.Bind();
    GLErrorManager(glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr, numInstances));
}

void Renderer::Draw(const Shader &shader, const VertexArray &va, unsigned int count, unsigned int numInstances) {
    shader.Bind();
    va.Bind();
    GLErrorManager(glDrawArraysInstanced(GL_TRIANGLES, 0, count, numInstances));
}

void Renderer::Clear() {
    GLErrorManager(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}



