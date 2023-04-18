//
// Created by Andrew Graser on 3/16/2023.
//

#ifndef OPENGL_BASE_TEXTURE2D_H
#define OPENGL_BASE_TEXTURE2D_H

#include "engine/ErrorManager.h"

//STD
#include <string>

class Texture2D{
private:
    unsigned int TYPE = GL_TEXTURE_2D;

    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;



public:
    Texture2D();
    Texture2D(const std::string& path);
    ~Texture2D();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const {return m_Width;}
    inline int GetHeight() const {return m_Height;}
    inline int GetHandle() const {return m_RendererID;}
};

#endif //OPENGL_BASE_TEXTURE2D_H
