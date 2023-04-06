//
// Created by Andrew Graser on 3/31/2023.
//

#include "IndexBuffer.h"
#include "engine/ErrorManager.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count) {
    ASSERT(sizeof(unsigned int) == sizeof(GLuint))

    GLErrorManager(glGenBuffers(1, &m_RendererID));
    GLErrorManager(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLErrorManager(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLErrorManager(glDeleteBuffers(1, &m_RendererID));
}


void IndexBuffer::Bind() const {
    GLErrorManager(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::unbind() const {
    GLErrorManager(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
