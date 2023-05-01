//
// Created by Andrew Graser on 4/29/2023.
//

#ifndef OPENGL_BASE_MESH_H
#define OPENGL_BASE_MESH_H

#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "renderer/Shader.h"
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;

    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;

    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;

    // constructor
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    // render the mesh
    void Draw(Shader &shader);

private:
    unsigned int VBO, EBO;

    std::unique_ptr<VertexArray> VA;
    std::unique_ptr<VertexBuffer> VB;
    std::unique_ptr<IndexBuffer> IB;

    void setupMesh();
};

#endif //OPENGL_BASE_MESH_H