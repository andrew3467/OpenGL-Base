//
// Created by Andrew Graser on 4/1/2023.
//

#pragma once

//#ifndef OPENGL_BASE_VERTEXARRAY_H
//#define OPENGL_BASE_VERTEXARRAY_H


#include "VertexBuffer.h"


class VertexBufferLayout;

class VertexArray{
private:
    unsigned int m_RendererID;

public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

//#endif //OPENGL_BASE_VERTEXARRAY_H
