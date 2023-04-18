//
// Created by apgra on 3/23/2023.
//

#include "Model.h"
#include "OBJ_Loader.h"
#include "renderer/VertexBufferLayout.h"

Model::Model(const std::string& path) {
    m_Directory = path.substr(0, path.find_last_of('/'));
    loadObj(path);
}

Model::~Model() {

}

void Model::Draw(Shader &shader) {
    if(!textures.empty()) {
        shader.Bind();

        for(unsigned int i = 0; i < textures.size(); i++) {
            textures[i].second.Bind(i);
            shader.SetInt("texture_" + textures[i].first, i);
        }
    }

    Renderer::Draw(shader, *VA, *IB);
}


void Model::loadObj(const std::string& path) {
    objl::Loader loader;
    loader.LoadFile(path);

    auto &mesh = loader.LoadedMeshes[0];

    for (auto &v: mesh.Vertices) {
        Vertex vertex;

        vertex.position.x = v.Position.X;
        vertex.position.y = v.Position.Y;
        vertex.position.z = v.Position.Z;

        vertex.normal.x = v.Normal.X;
        vertex.normal.y = v.Normal.Y;
        vertex.normal.z = v.Normal.Z;

        vertex.uv.x = v.TextureCoordinate.X;
        vertex.uv.y = v.TextureCoordinate.Y;

        vertices.push_back(vertex);
    }

    for (auto &i: mesh.Indices) {
        indices.push_back(i);
    }
    if (!loader.LoadedMaterials.empty()) {
        auto material = loader.LoadedMaterials[1];

        textures.emplace_back("diffuse", m_Directory + "/" + material.map_Kd);
        textures.emplace_back("roughness", m_Directory + "/" + material.map_Ks);


        //Create VAO
        VA = std::make_unique<VertexArray>();
        VB = std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(Vertex));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);
        VA->AddBuffer(*VB, layout);

        IB = std::make_unique<IndexBuffer>(&indices[0], indices.size());
    }
}