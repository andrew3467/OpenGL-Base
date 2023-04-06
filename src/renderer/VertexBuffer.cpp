//
// Created by Andrew Graser on 3/31/2023.
//

#include "VertexBuffer.h"
#include "engine/ErrorManager.h"

VertexBuffer::VertexBuffer() : m_RendererID(0) {

}

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    GLErrorManager(glGenBuffers(1, &m_RendererID));
    GLErrorManager(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLErrorManager(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GLErrorManager(glDeleteBuffers(1, &m_RendererID));
}



void VertexBuffer::Bind() const {
    GLErrorManager(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const {
    GLErrorManager(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
