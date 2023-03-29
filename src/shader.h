//
// Created by Andrew Graser on 2/26/2023.
//

#ifndef HELLO_WINDOW_SHADER_H
#define HELLO_WINDOW_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <lights.h>


class Shader{
private:
    unsigned int handle;

public:
    Shader(const char *vertPath, const char *fragPath, const char* geometryPath = nullptr);
    ~Shader();

private:
    unsigned int createShaderProgram(const char* vertPath, const char* fragPath, const char* geometryPath);
    std::string readSourceFile(const char* srcPath);
    unsigned int createShader(unsigned int SHADER_TYPE, const char *src);

public:
    void bind() const;
    void unbind() const;


    //Uniforms
private:
    int location(const std::string& n) const;

public:
    void setPointLight(const PointLight& light, const std::string& arrIndex);


    void setInt(const std::string& name, int v);
    void setFloat(const std::string& name, float v);

    void setVec4(const std::string& name, glm::vec4 v);
    void setVec4(const std::string& name, float x, float y, float z, float w);

    void setVec3(const std::string& name, glm::vec3 v);
    void setVec3(const std::string& name, float x, float y, float z);
    void setVec3(const std::string& name, float v);

    void setVec2(const std::string& name, glm::vec2 v);
    void setVec2(const std::string& name, float x, float y);

    void setMat4(const std::string& name, glm::mat4 v);
};

#endif //HELLO_WINDOW_SHADER_H
