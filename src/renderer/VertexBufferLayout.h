//
// Created by Andrew Graser on 4/1/2023.
//

#ifndef OPENGL_BASE_VERTEXBUFFERLAYOUT_H
#define OPENGL_BASE_VERTEXBUFFERLAYOUT_H


#include <vector>
#include "engine/ErrorManager.h"

struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    bool normalized;

    static unsigned int GetSizeOfType(unsigned int type){
        switch(type){
            case GL_FLOAT: return sizeof(float);
            case GL_UNSIGNED_INT: return sizeof(unsigned int);
            case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
            case GL_INT: return sizeof(int);
        }
        ASSERT(false)

        return 0;
    }
};

class VertexBufferLayout{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout() : m_Stride(0) {

    }

    template<typename T>
    void Push(unsigned int count){
        //static_assert(false);
    }

    template<>
    void Push<float>(unsigned int count){
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
    }

    template<>
    void Push<unsigned int>(unsigned int count){
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
    }

    template<>
    void Push<unsigned char>(unsigned int count){
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
    }

    template<>
    void Push<int>(unsigned int count){
        m_Elements.push_back({GL_INT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_INT) * count;
    }

    inline std::vector<VertexBufferElement> GetElements() const {return m_Elements;}
    inline unsigned int GetStride() const {return m_Stride;}
};

#endif //OPENGL_BASE_VERTEXBUFFERLAYOUT_H
