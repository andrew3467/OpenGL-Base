//
// Created by apgra on 3/22/2023.
//

#ifndef OPENGL_BASE_MESH_H
#define OPENGL_BASE_MESH_H

#include <vector>
#include <string>

#include "glm/glm.hpp"

#include "renderer/Shader.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    glm::vec4 m_BoneIDs;
    glm::vec4 m_Weights;
};

class Mesh{
public:
    struct Texture{
        unsigned int ID;
        std::string type;
        std::string path;
    };

    //MeshData
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<Texture> t);
    void Draw(Shader* shader, int numInstances = 1);

private:
    VertexBuffer VB;
    IndexBuffer IB;
    VertexArray VA;

    void setupMesh();
};

#endif //OPENGL_BASE_MESH_H
