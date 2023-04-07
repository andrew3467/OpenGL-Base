//
// Created by Andrew Graser on 4/3/2023.
//

#pragma once
//#ifndef OPENGL_BASE_RENDERER_H
//#define OPENGL_BASE_RENDERER_H


#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"


class Renderer {
public:
    void Clear();
    void Draw(const Shader& shader, const VertexArray& va, const IndexBuffer& ib) const;

private:

};

//#endif //OPENGL_BASE_RENDERER_H
