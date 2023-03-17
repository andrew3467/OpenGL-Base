//
// Created by Andrew Graser on 3/16/2023.
//
#include "texture2d.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

Texture2D::Texture2D(const std::string& texPath) {
    handle = CreateTexture(texPath);
}

unsigned int Texture2D::CreateTexture(const std::string& path) {
    unsigned char* texData = loadTexture(path);

    unsigned int tex;
    glGenTextures(1, &tex);
    glBindTexture(TYPE, tex);

    //Textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(TYPE, 0);
    return tex;
}

unsigned char *Texture2D::loadTexture(const std::string& path) {
    if(path.empty()){
        throw std::runtime_error("ERROR: Texture received null source");
    }
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    return data;
}

void Texture2D::bind() const {
    glBindTexture(TYPE, handle);
}

void Texture2D::unbind() const {
    glBindTexture(TYPE, 0);
}

//Cleanup
Texture2D::~Texture2D() {
    glDeleteTextures(1, &handle);
}

