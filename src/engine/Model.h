//
// Created by apgra on 3/23/2023.
//

#ifndef OPENGL_BASE_MODEL_H
#define OPENGL_BASE_MODEL_H

#include <string>
#include <vector>

#include "renderer/Shader.h"

#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Renderer.h"
#include "renderer/Texture2D.h"

class Model {
    struct Vertex{
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

private:
    std::string m_Directory;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    std::unique_ptr<VertexArray> VA;
    std::unique_ptr<VertexBuffer> VB;
    std::unique_ptr<IndexBuffer> IB;

    std::unique_ptr<Texture2D> texDiffuse;
    std::unique_ptr<Texture2D> texRoughness;
    std::unique_ptr<Texture2D> texNormal;
    std::unique_ptr<Texture2D> texAO;
    std::unique_ptr<Texture2D> texMetallic;

public:
    Model(const std::string& path);
    ~Model();

    void Draw(Shader& shader);

private:
    void loadObj(const std::string& path);
};

#endif //OPENGL_BASE_MODEL_H