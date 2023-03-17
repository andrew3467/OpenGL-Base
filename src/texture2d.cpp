//
// Created by Andrew Graser on 3/16/2023.
//
#include "texture2d.h"

#include <stb_image.h>

Texture2D::Texture2D(const std::string& path) : handle(0), filePath(path), localBuffer(nullptr), width(0), height(0), BPP(0) {
    stbi_set_flip_vertically_on_load(true);
    localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);

    glGenTextures(1, &handle);
    glBindTexture(TYPE, handle);

    glTexParameteri(TYPE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(TYPE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(TYPE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(TYPE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(TYPE, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

    glBindTexture(TYPE, 0);

    if(localBuffer) {
        stbi_image_free(localBuffer);
    }
}



void Texture2D::bind(unsigned int slot = 0) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(TYPE, handle);
}

void Texture2D::unbind() const {
    glBindTexture(TYPE, 0);
}

//Cleanup
Texture2D::~Texture2D() {
    glDeleteTextures(1, &handle);
}