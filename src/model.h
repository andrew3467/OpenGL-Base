//
// Created by apgra on 3/23/2023.
//

#ifndef OPENGL_BASE_MODEL_H
#define OPENGL_BASE_MODEL_H

#include <string>
#include <vector>

#include <shader.h>
#include <mesh.h>

#include <assimp/scene.h>
#include <stb_image.h>


class Model{
private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Mesh::Texture> textures_loaded;

    bool gammaCorrection;

public:
    Model(const char* path, bool gamma = false);
    void draw(Shader* shader, int numInstances = 1);

private:
    void loadModel(std::string const &path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Mesh::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string name);

    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
};

#endif //OPENGL_BASE_MODEL_H
