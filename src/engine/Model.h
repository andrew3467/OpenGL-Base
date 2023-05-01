//
// Created by apgra on 3/23/2023.
//

#ifndef OPENGL_BASE_MODEL_H
#define OPENGL_BASE_MODEL_H

#include <glad/glad.h>

#include <assimp/scene.h>
#include <glm/glm.hpp>

#include "Mesh.h"

#include <string>


#include <vector>


unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
public:
    std::vector<Texture> textures_loaded;
    std::vector<Mesh>    meshes;
    std::string directory;
    bool gammaCorrection;


    Model(std::string const &path, bool gamma = false);

    void Draw(Shader &shader);

private:
    void loadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
};


#endif //OPENGL_BASE_MODEL_H