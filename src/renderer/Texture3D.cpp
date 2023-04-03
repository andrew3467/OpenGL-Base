//
// Created by apgra on 3/19/2023.
//

#include "Texture3D.h"
#include <stdexcept>
#include "stb_image.h"

#include <iostream>


Texture3D::Texture3D() : m_RendererID(0) {

}

Texture3D::Texture3D(std::vector<std::string> faces) : m_RendererID(0)
{
    m_RendererID = loadCubemap(faces);
}

unsigned int Texture3D::loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    GLCall(glGenTextures(1, &textureID));
    GLCall(glBindTexture(TYPE, textureID));

    stbi_set_flip_vertically_on_load(false);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        }
        else
        {
            throw std::runtime_error("Cubemap texture failed to load at path: " + faces[i]);
        }
        stbi_image_free(data);
    }
    GLCall(glTexParameteri(TYPE, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(TYPE, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(TYPE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(TYPE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(TYPE, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

    return textureID;
}

void Texture3D::bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(TYPE, m_RendererID));
}

void Texture3D::unbind() const {
    GLCall(glBindTexture(TYPE, 0));
}

//Cleanup
Texture3D::~Texture3D() {
    GLCall(glDeleteTextures(1, &m_RendererID));
}

