//
// Created by Andrew Graser on 2/26/2023.
//

#include "shader.h"


Shader::Shader(const char *vertPath, const char *fragPath) {
    handle = createShaderProgram(vertPath, fragPath);
}

unsigned int Shader::createShaderProgram(const char *vertPath, const char *fragPath) {
    unsigned int vert, frag;
    vert = createShader(GL_VERTEX_SHADER, readSourceFile(vertPath).c_str());
    frag = createShader(GL_FRAGMENT_SHADER, readSourceFile(fragPath).c_str());

    unsigned int id = glCreateProgram();
    glAttachShader(id, vert);
    glAttachShader(id, frag);
    glLinkProgram(id);

    int success;
    char infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILURE\n" << infoLog << "\n";
    }

    //Cleanup
    glDeleteShader(vert);
    glDeleteShader(frag);

    return id;
}

unsigned int Shader::createShader(unsigned int SHADER_TYPE, const char *src) {
    if(src == nullptr){
        throw std::runtime_error("ERROR: Shader received null source");
    }
    unsigned int shader = glCreateShader(SHADER_TYPE);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);


    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::" << ((SHADER_TYPE == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT") << "::SHADER::COMPILATION_FAILED\n" << infoLog << "\n";
    }

    return shader;
}

std::string Shader::readSourceFile(const char* srcPath) {
    std::ifstream file;
    std::stringstream stream;

    file.open(srcPath);
    stream << file.rdbuf();

    return stream.str();
}

void Shader::bind() const {
    glUseProgram(handle);
}

void Shader::unbind() const {
    glUseProgram(0);
}

int Shader::location(const std::string& n) const {

    return glGetUniformLocation(handle, n.c_str());
}


void Shader::setInt(const std::string &name, int v) {
    glUniform1i(location(name), v);
}

void Shader::setFloat(const std::string &name, float v) {
    glUniform1f(location(name), v);
}


void Shader::setVec3(const std::string &name, glm::vec3 v) {
    glUniform3f(location(name), v.x, v.y, v.z);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) {
    glUniform3f(location(name), x, y, z);
}

void Shader::setVec3(const std::string &name, float v) {
    glUniform3f(location(name), v, v, v);
}

void Shader::setVec4(const std::string& name, glm::vec4 v) {
    glUniform4f(location(name), v.x, v.y, v.z, v.w);
}


void Shader::setMat4(const std::string &name, glm::mat4 v) {
    glUniformMatrix4fv(location(name), 1, GL_FALSE, glm::value_ptr(v));
}


//Cleanup
Shader::~Shader() {
    glDeleteProgram(handle);
}
