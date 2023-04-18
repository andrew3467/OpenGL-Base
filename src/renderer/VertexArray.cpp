//
// Created by Andrew Graser on 4/1/2023.
//

#include "engine/ErrorManager.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"


VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray() {
    GLErrorManager(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;

    for(unsigned int i = 0; i < elements.size(); i++){
        const auto &element = elements[i];
        GLErrorManager(glEnableVertexAttribArray(i));
        GLErrorManager(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count *  VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const {
    GLErrorManager(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const {
    GLErrorManager(glBindVertexArray(0))
}
