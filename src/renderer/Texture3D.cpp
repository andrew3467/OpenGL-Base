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
    GLErrorManager(glGenTextures(1, &textureID));
    GLErrorManager(glBindTexture(TYPE, textureID));

    stbi_set_flip_vertically_on_load(false);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLErrorManager(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        }
        else
        {
            throw std::runtime_error("Cubemap texture failed to load at path: " + faces[i]);
        }
        stbi_image_free(data);
    }
    GLErrorManager(glTexParameteri(TYPE, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLErrorManager(glTexParameteri(TYPE, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLErrorManager(glTexParameteri(TYPE, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLErrorManager(glTexParameteri(TYPE, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLErrorManager(glTexParameteri(TYPE, GL_TEXTURE_WRAP_R, GL_REPEAT));

    return textureID;
}

void Texture3D::Bind(unsigned int slot) const {
    GLErrorManager(glActiveTexture(GL_TEXTURE0 + slot));
    GLErrorManager(glBindTexture(TYPE, m_RendererID));
}

void Texture3D::Unbind() const {
    GLErrorManager(glBindTexture(TYPE, 0));
}

//Cleanup
Texture3D::~Texture3D() {
    GLErrorManager(glDeleteTextures(1, &m_RendererID));
}

