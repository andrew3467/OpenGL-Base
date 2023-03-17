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


class Shader{
private:
    unsigned int handle;

public:
    Shader(const char*, const char*);
    ~Shader();

private:
    unsigned int createShaderProgram(const char*, const char*);
    std::string readSourceFile(const char*);
    unsigned int createShader(unsigned int, const char*);

public:
    void bind() const;
    void unbind() const;


    //Uniforms
private:
    int location(const std::string& n) const;

public:
    void setInt(const std::string& name, int v);

    void setVec4(const std::string& name, glm::vec4 v);
    void setVec3(const std::string& name, glm::vec3 v);

    void setMat4(const std::string& name, glm::mat4 v);
};

#endif //HELLO_WINDOW_SHADER_H
