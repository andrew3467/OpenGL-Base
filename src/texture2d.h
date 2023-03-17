//
// Created by Andrew Graser on 3/16/2023.
//

#ifndef OPENGL_BASE_TEXTURE2D_H
#define OPENGL_BASE_TEXTURE2D_H

#include <glad/glad.h>

//STD
#include <string>

class Texture2D{
private:
    unsigned int TYPE = GL_TEXTURE_2D;

    unsigned int handle;
    std::string filePath;
    unsigned char* localBuffer;
    int width, height, BPP;



public:
    Texture2D(const std::string& path);
    ~Texture2D();

    void bind(unsigned int slot);
    void unbind() const;

    inline int getWidth() const {return width;}
    inline int getHeight() const {return height;}
};

#endif //OPENGL_BASE_TEXTURE2D_H
