//
// Created by Andrew Graser on 3/16/2023.
//
#include "Texture2D.h"

#include "stb_image.h"
#include <iostream>



Texture2D::Texture2D() : m_RendererID(0) {

}

Texture2D::Texture2D(const std::string& path) : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0) {
    if (path.empty()) {
        throw std::runtime_error("ERROR: Texture received null path");
    }

    stbi_set_flip_vertically_on_load(true);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    if (m_LocalBuffer == nullptr) {
        throw std::runtime_error("ERROR: Failed to load texture");
    }

    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(TYPE, m_RendererID));

    GLCall(glTexParameteri(TYPE, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glTexParameteri(TYPE, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glTexParameteri(TYPE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(TYPE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(TYPE, 0, GL_SRGB8_ALPHA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    GLCall(glGenerateMipmap(TYPE));

    GLCall(glBindTexture(TYPE, 0));

    stbi_image_free(m_LocalBuffer);
}



void Texture2D::Bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(TYPE, m_RendererID));
}

void Texture2D::Unbind() const {
    GLCall(glBindTexture(TYPE, 0));
}

//Cleanup
Texture2D::~Texture2D() {
    GLCall(glDeleteTextures(1, &m_RendererID));
}
