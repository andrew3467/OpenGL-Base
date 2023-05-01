//
// Created by Andrew Graser on 4/29/2023.
//

#include "Mesh.h"

#include "renderer/Renderer.h"



Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}


void Mesh::Draw(Shader &shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string


        shader.SetInt(name + number, i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    Renderer::Draw(shader, *VA, *IB);


    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh() {
    VA = std::make_unique<VertexArray>();
    VB = std::make_unique<VertexBuffer>(&vertices[0], vertices.size());

    VertexBufferLayout layout;
    layout.Push<float>(3);  //Position
    layout.Push<float>(3);  //Normal
    layout.Push<float>(2);  //UV
    layout.Push<float>(3);  //Tangent
    layout.Push<float>(3);  //BiTangent
    layout.Push<int>(4);    //Bone IDS
    layout.Push<float>(4);    //Bone Weights

    VA->AddBuffer(*VB, layout);

    IB = std::make_unique<IndexBuffer>(&indices[0], indices.size());
}
