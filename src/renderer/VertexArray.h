//
// Created by Andrew Graser on 4/1/2023.
//

#ifndef OPENGL_BASE_VERTEXARRAY_H
#define OPENGL_BASE_VERTEXARRAY_H


#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray{
private:
    unsigned int m_RendererID;

public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

#endif //OPENGL_BASE_VERTEXARRAY_H
