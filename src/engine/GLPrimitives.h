//
// Created by apgra on 3/25/2023.
//

#ifndef OPENGL_BASE_GLPRIMITIVES_H
#define OPENGL_BASE_GLPRIMITIVES_H

#include "glm/glm.hpp"

#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/Shader.h"

namespace glPrimitive {
    float planeVertices[48] = {
            // positions                // normals                          // texcoords
            0.5, -0.5f,  0.5,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
            -0.5, -0.5f,  0.5,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -0.5, -0.5f, -0.5,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

            0.5, -0.5f,  0.5,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
            -0.5, -0.5f, -0.5,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
            0.5, -0.5f, -0.5,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f
    };

    void DrawPlane(Shader* shader, glm::vec3 position, glm::vec3 scale){
        VertexArray va;
        VertexBuffer vb(planeVertices, sizeof(planeVertices) * 4);

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, position);
        trans = glm::scale(trans, scale);

        shader->Bind();
        shader->SetMat4("model", trans);

        va.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        va.Unbind();
    }
}

#endif //OPENGL_BASE_GLPRIMITIVES_H
