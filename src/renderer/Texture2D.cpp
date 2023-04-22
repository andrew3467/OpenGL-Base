//
// Created by Andrew Graser on 3/16/2023.
//
#include "Texture2D.h"

#include "stb_image.h"
#include <iostream>



Texture2D::Texture2D() : m_RendererID(0) {

}

Texture2D::Texture2D(const std::string& path, bool alpha) : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0) {
    if (path.empty()) {
        throw std::runtime_error("ERROR: Texture received null path");
    }

    stbi_set_flip_vertically_on_load(true);

    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);


    if (m_LocalBuffer == nullptr) {
        throw std::runtime_error("ERROR: Failed to load texture");
    }

    GLErrorManager(glGenTextures(1, &m_RendererID));
    GLErrorManager(glBindTexture(TYPE, m_RendererID));

    GLErrorManager(glTexParameteri(TYPE, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLErrorManager(glTexParameteri(TYPE, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLErrorManager(glTexParameteri(TYPE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLErrorManager(glTexParameteri(TYPE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLErrorManager(glTexImage2D(TYPE, 0, GL_SRGB8_ALPHA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    GLErrorManager(glGenerateMipmap(TYPE));

    GLErrorManager(glBindTexture(TYPE, 0));

    stbi_image_free(m_LocalBuffer);
}



void Texture2D::Bind(unsigned int slot) const {
    GLErrorManager(glActiveTexture(GL_TEXTURE0 + slot));
    GLErrorManager(glBindTexture(TYPE, m_RendererID));
}

void Texture2D::Unbind() const {
    GLErrorManager(glBindTexture(TYPE, 0));
}

//Cleanup
Texture2D::~Texture2D() {
    GLErrorManager(glDeleteTextures(1, &m_RendererID));
}
