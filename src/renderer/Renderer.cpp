//
// Created by Andrew Graser on 4/3/2023.
//
#include "Renderer.h"
#include "engine/ErrorManager.h"


void Renderer::Draw(const Shader& shader, const VertexArray &va, const IndexBuffer &ib) {
    shader.Bind();
    va.Bind();
    GLErrorManager(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const Shader &shader, const VertexArray &va, unsigned int count) {
    shader.Bind();
    va.Bind();
    GLErrorManager(glDrawArrays(GL_TRIANGLES, 0, count));
}

void Renderer::Clear() {
    GLErrorManager(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}



