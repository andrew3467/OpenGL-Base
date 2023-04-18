//
// Created by apgra on 3/19/2023.
//

#ifndef OPENGL_BASE_TEXTURE3D_H
#define OPENGL_BASE_TEXTURE3D_H

#include "engine/ErrorManager.h"

#include <string>
#include <vector>

class Texture3D{
private:
    unsigned int TYPE = GL_TEXTURE_CUBE_MAP;

    unsigned int m_RendererID;
    std::string filePaths[6];

    // loads a skybox texture from 6 individual texture faces
    // +X (right)
    // -X (left)
    // +Y (top)
    // -Y (bottom)
    // +Z (front)
    // -Z (back)
    unsigned int loadCubemap(std::vector<std::string> faces);
    unsigned int loadHDR(const std::string& path);

public:
    Texture3D();
    Texture3D(std::vector<std::string> faces);
    Texture3D(const std::string& path);
    ~Texture3D();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
};

#endif //OPENGL_BASE_TEXTURE3D_H
