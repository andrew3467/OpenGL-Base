//
// Created by apgra on 3/24/2023.
//

#include <primitives.h>

unsigned int Primitive::cubeVAO = 0;


void Primitive::drawCube(Shader *shader, glm::vec3 position, glm::vec3 scale) {
    if(!cubeVAO){
        unsigned int VBO;
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(cubeVAO);

        glBindBuffer(GL_VERTEX_ARRAY, VBO);
        glBufferData(GL_VERTEX_ARRAY, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

        //Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
        //TexCoords
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
    }

    glm::mat4 trans = glm::mat4(1.0);
    trans = glm::translate(trans, position);
    trans = glm::scale(trans, scale);

    shader->setMat4("model", trans);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}
