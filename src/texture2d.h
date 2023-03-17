//
// Created by Andrew Graser on 3/16/2023.
//

#ifndef OPENGL_BASE_TEXTURE2D_H
#define OPENGL_BASE_TEXTURE2D_H

#include <glad/glad.h>

//STD
#include <string>

class Texture2D{
public:
    Texture2D(const std::string& texPath);
    ~Texture2D();

private:
    int TYPE = GL_TEXTURE_2D;
    unsigned int handle;

    int width, height, channels;


    unsigned int CreateTexture(const std::string& path);
    unsigned char* loadTexture(const std::string& path);

public:
    void bind() const;
    void unbind() const;
};

#endif //OPENGL_BASE_TEXTURE2D_H
