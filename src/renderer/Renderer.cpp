//
// Created by Andrew Graser on 4/3/2023.
//
#include "Renderer.h"
#include "engine/ErrorManager.h"


void Renderer::Draw(Shader *shader, const VertexArray &va, const IndexBuffer &ib) const {
    shader->Bind();
    va.Bind();
    ib.Bind();
    GLErrorManager(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() {
    GLErrorManager(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}



