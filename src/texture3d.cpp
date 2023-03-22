//
// Created by apgra on 3/19/2023.
//

#include <texture3d.h>
#include <stdexcept>
#include <stb_image.h>

Texture3D::Texture3D(const std::string &path) : handle(0), filePath(path), localBuffer(nullptr),
    width(0), height(0), BPP(0)
{
    if(path.empty()){
        throw std::runtime_error("ERROR: Texture received null path");
    }

    stbi_set_flip_vertically_on_load(true);
    localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 0);

    if(localBuffer == nullptr){
        throw std::runtime_error("ERROR: Failed to load texture");
    }

    glGenTextures(1, &handle);
    glBindTexture(TYPE, handle);

    glTexParameteri(TYPE, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(TYPE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(TYPE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(TYPE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(TYPE, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    //Create a texture for each face
    for (int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
    }

    stbi_image_free(localBuffer);
}

void Texture3D::bind(unsigned int slot = 0) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(TYPE, handle);
}

void Texture3D::unbind() const {
    glBindTexture(TYPE, 0);
}

//Cleanup
Texture3D::~Texture3D() {
    glDeleteTextures(1, &handle);
}
