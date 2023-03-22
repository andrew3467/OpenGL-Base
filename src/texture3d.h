//
// Created by apgra on 3/19/2023.
//

#ifndef OPENGL_BASE_TEXTURE3D_H
#define OPENGL_BASE_TEXTURE3D_H

#include <GLAD/glad.h>

#include <string>

class Texture3D{
private:
    unsigned int TYPE = GL_TEXTURE_CUBE_MAP;

    unsigned int handle;
    std::string filePath;
    unsigned char* localBuffer;
    int width, height, BPP;

public:
    Texture3D(const std::string& path);
    ~Texture3D();

    void bind(unsigned int slot) const;
    void unbind() const;

    inline int getWidth() const {return width;}
    inline int getHeight() const {return height;}
};

#endif //OPENGL_BASE_TEXTURE3D_H
