//
// Created by Andrew Graser on 2/26/2023.
//

#ifndef HELLO_WINDOW_SHADER_H
#define HELLO_WINDOW_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>



#include "glm/glm.hpp"
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "engine/Lights.h"


class Shader{
private:
    unsigned int m_RendererID;
    mutable std::unordered_map<std::string, int> m_UniformCache;

public:
    Shader();
    Shader(const char *vertPath, const char *fragPath, const char* geometryPath = nullptr);
    ~Shader();

private:
    unsigned int createShaderProgram(const char* vertPath, const char* fragPath, const char* geometryPath);
    std::string readSourceFile(const char* srcPath);
    unsigned int createShader(unsigned int SHADER_TYPE, const char *src);
    int getUniformLocation(const std::string& name) const;

public:
    void Bind() const;
    void Unbind() const;

    inline unsigned int getID() {return m_RendererID;}

//Uniforms
public:
    void SetPointLight(const PointLight& light, const std::string& arrIndex);


    void SetInt(const std::string& name, int v);
    void SetFloat(const std::string& name, float v);

    void setVec4(const std::string& name, glm::vec4 v);
    void setVec4(const std::string& name, float x, float y, float z, float w);

    void SetVec3(const std::string& name, glm::vec3 v);
    void SetVec3(const std::string& name, float x, float y, float z);
    void setVec3(const std::string& name, float v);

    void setVec2(const std::string& name, glm::vec2 v);
    void setVec2(const std::string& name, float x, float y);

    void SetMat4(const std::string& name, glm::mat4 v);
};

#endif //HELLO_WINDOW_SHADER_H
