//
// Created by apgra on 3/22/2023.
//
#include "Mesh.h"
#include "renderer/VertexBufferLayout.h"


Mesh::Mesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<Texture> t) :
        vertices(v), indices(i), textures(t) {
    setupMesh();
}

void Mesh::setupMesh()
{
    // create buffers/arrays
    VB = VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));
    IB = IndexBuffer(&indices[0], indices.size() * sizeof(unsigned int));

    VertexBufferLayout layout;
    layout.Push<float>(3);  //Position
    layout.Push<float>(3);  //Normals
    layout.Push<float>(2);  //TexCoords
    layout.Push<float>(3);  //Tangent
    layout.Push<float>(4);  //Bitangent
    layout.Push<int>(4);    //Bone IDS
    layout.Push<float>(4);  //Bone Weights

    /*
    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
    */
}

void Mesh::Draw(Shader* shader, int numInstances)
{
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        GLErrorManager(glActiveTexture(GL_TEXTURE0 + i));

        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if(name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if(name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string


        shader->SetInt(name + number, i);
        GLErrorManager(glBindTexture(GL_TEXTURE_2D, textures[i].ID));
    }

    // draw mesh
    VA.Bind();
    //glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    GLErrorManager(glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr, numInstances));
    VA.Unbind();

    GLErrorManager(glActiveTexture(GL_TEXTURE0));
}

