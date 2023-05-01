//
// Created by apgra on 3/23/2023.
//

#ifndef OPENGL_BASE_MODEL_H
#define OPENGL_BASE_MODEL_H

#include <string>
#include "Mesh.h"
#include "assimp/scene.h"
#include <assimp/IOStream.hpp>
#include <assimp/IOSystem.hpp>


typedef std::pair<std::vector<Mesh::Vertex>, std::vector<unsigned int>> MeshData;


class Model {
public:
    Model(const std::string& path);
    ~Model();

    void Draw(const Shader& shader);

private:
    void loadModelData(const std::string& modelPath);
    void processNode(const aiNode* node, const aiScene* scene);
    MeshData processMesh(const aiMesh* mesh, const aiScene* scene);


private:
    std::string m_Filename;
    std::vector<Mesh> m_Meshes;
};




#endif //OPENGL_BASE_MODEL_H