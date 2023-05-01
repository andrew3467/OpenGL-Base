//
// Created by Andrew Graser on 4/29/2023.
//

#ifndef OPENGL_BASE_MESH_H
#define OPENGL_BASE_MESH_H


#include <memory>
#include <vector>
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shader.h"
#include <glm/glm.hpp>

class Mesh {
public:
    struct Vertex{
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 UV;
    };

public:
    Mesh(const Mesh &){}
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Draw(const Shader& shader);

private:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;

    std::unique_ptr<VertexArray> VA;
    std::unique_ptr<VertexBuffer> VB;
    std::unique_ptr<IndexBuffer> IB;

    unsigned int VBO, EBO, VAO;
};


#endif //OPENGL_BASE_MESH_H
