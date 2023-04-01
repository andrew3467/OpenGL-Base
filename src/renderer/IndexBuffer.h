//
// Created by Andrew Graser on 3/31/2023.
//

#ifndef OPENGL_BASE_INDEXBUFFER_H
#define OPENGL_BASE_INDEXBUFFER_H

#include <glad/glad.h>

class IndexBuffer {
private:
    unsigned int m_RendererID;
    unsigned int m_Count;

public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int GetCount() const { return  m_Count;}
};

#endif //OPENGL_BASE_INDEXBUFFER_H