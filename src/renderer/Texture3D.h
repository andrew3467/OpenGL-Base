//
// Created by apgra on 3/19/2023.
//

#ifndef OPENGL_BASE_TEXTURE3D_H
#define OPENGL_BASE_TEXTURE3D_H

#include "Renderer.h"

#include <string>
#include <vector>

class Texture3D{
private:
    unsigned int TYPE = GL_TEXTURE_CUBE_MAP;

    unsigned int m_RendererID;
    std::string filePaths[6];

    // loads a cubemap texture from 6 individual texture faces
    // +X (right)
    // -X (left)
    // +Y (top)
    // -Y (bottom)
    // +Z (front)
    // -Z (back)
    unsigned int loadCubemap(std::vector<std::string> faces);

public:
    Texture3D();
    Texture3D(std::vector<std::string> faces);
    ~Texture3D();

    void bind(unsigned int slot = 0) const;
    void unbind() const;
};

#endif //OPENGL_BASE_TEXTURE3D_H
