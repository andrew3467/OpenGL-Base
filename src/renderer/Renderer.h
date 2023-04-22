//
// Created by Andrew Graser on 4/3/2023.
//

#pragma once
//#ifndef OPENGL_BASE_RENDERER_H
//#define OPENGL_BASE_RENDERER_H


#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"


class Renderer {
public:
    static void Clear();
    static void Draw(const Shader& shader, const VertexArray& va, const IndexBuffer& ib, unsigned int numInstances = 1);
    static void Draw(const Shader& shader, const VertexArray& va, unsigned int count, unsigned int numInstances = 1);

    static void DrawQuad(const Shader& shader) {
        static VertexArray* VA;
        static VertexBuffer* VB;
        static IndexBuffer* IB;

        if(VA == nullptr){
            float vertices[] = {
                    -1.0f, -1.0f, 0.0f,         0.0f, 0.0f,
                    1.0f, -1.0f, 0.0f,          1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,        1.0f, 1.0f,
                    -1.0f, 1.0f, 0.0f,       0.0f, 1.0f
            };

            unsigned int indices[6] = {
                    0, 1, 2,
                    2, 3, 0
            };

            VA = new VertexArray();
            VB = new VertexBuffer(vertices, sizeof(vertices));

            VertexBufferLayout layout;
            layout.Push<float>(3);
            layout.Push<float>(2);
            VA->AddBuffer(*VB, layout);

            IB = new IndexBuffer(indices, sizeof(indices));
        }

        Draw(shader, *VA, *IB);
    }
};

//#endif //OPENGL_BASE_RENDERER_H
