//
// Created by Andrew Graser on 3/31/2023.
//

#ifndef OPENGL_BASE_VERTEXBUFFER_H
#define OPENGL_BASE_VERTEXBUFFER_H

#include <glad/glad.h>

class VertexBuffer{
private:
    unsigned int m_RendererID;

public:
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer();
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

#endif //OPENGL_BASE_VERTEXBUFFER_H
