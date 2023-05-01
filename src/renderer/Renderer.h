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

    inline static void DrawQuad(const Shader& shader) {
        static std::unique_ptr<VertexArray> VA;
        static std::unique_ptr<VertexBuffer> VB;
        static std::unique_ptr<IndexBuffer> IB;

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

            VA = std::make_unique<VertexArray>();
            VB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

            VertexBufferLayout layout;
            layout.Push<float>(3);
            layout.Push<float>(2);
            VA->AddBuffer(*VB, layout);

            IB = std::make_unique<IndexBuffer>(indices, sizeof(indices));
        }

        Draw(shader, *VA, *IB);
    }

    inline static void DrawCube(const Shader& shader) {
        static std::unique_ptr<VertexArray> VA;
        static std::unique_ptr<VertexBuffer> VB;
        static std::unique_ptr<IndexBuffer> IB;

        if(VA == nullptr){
            float vertices[] = {
                    -0.5, -0.5,  0.5, //0
                    0.5, -0.5,  0.5, //1
                    -0.5,  0.5,  0.5, //2
                    0.5,  0.5,  0.5, //3
                    -0.5, -0.5, -0.5, //4
                    0.5, -0.5, -0.5, //5
                    -0.5,  0.5, -0.5, //6
                    0.5,  0.5, -0.5  //7
            };

            unsigned int indices[36] = {
                    //Top
                    2, 6, 7,
                    2, 3, 7,

                    //Bottom
                    0, 4, 5,
                    0, 1, 5,

                    //Left
                    0, 2, 6,
                    0, 4, 6,

                    //Right
                    1, 3, 7,
                    1, 5, 7,

                    //Front
                    0, 2, 3,
                    0, 1, 3,

                    //Back
                    4, 6, 7,
                    4, 5, 7
            };

            VA = std::make_unique<VertexArray>();
            VB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

            VertexBufferLayout layout;
            layout.Push<float>(3);
            VA->AddBuffer(*VB, layout);

            IB = std::make_unique<IndexBuffer>(indices, sizeof(indices));
        }

        Draw(shader, *VA, *IB);
    }
};

//#endif //OPENGL_BASE_RENDERER_H
