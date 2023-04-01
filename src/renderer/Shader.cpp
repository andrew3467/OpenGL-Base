//
// Created by Andrew Graser on 2/26/2023.
//

#include "Shader.h"


Shader::Shader(const char *vertPath, const char *fragPath, const char* geometryPath) {
    handle = createShaderProgram(vertPath, fragPath, geometryPath);
}

unsigned int Shader::createShaderProgram(const char *vertPath, const char *fragPath, const char* geometryPath) {
    unsigned int vert, frag, geom;
    vert = createShader(GL_VERTEX_SHADER, readSourceFile(vertPath).c_str());
    frag = createShader(GL_FRAGMENT_SHADER, readSourceFile(fragPath).c_str());
    if(geometryPath != nullptr){
        geom = createShader(GL_GEOMETRY_SHADER, readSourceFile(geometryPath).c_str());
    }
    unsigned int id = glCreateProgram();
    glAttachShader(id, vert);
    glAttachShader(id, frag);
    if(geometryPath != nullptr)
        glAttachShader(id, geom);
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
    if(geometryPath != nullptr)
        glDeleteShader(geom);

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

    try{
        file.open(srcPath);
        stream << file.rdbuf();
    }catch(std::exception& e){
        throw std::runtime_error(e.what());
    }


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



void Shader::setPointLight(const PointLight &light, const std::string& arrIndex) {
    setVec3("pointLights[" + arrIndex + "].position", light.position);

    setVec3("pointLights[" + arrIndex + "].ambient", light.ambient);
    setVec3("pointLights[" + arrIndex + "].diffuse", light.diffuse);
    setVec3("pointLights[" + arrIndex + "].specular", light.specular);

    setVec3("pointLights[" + arrIndex + "].constant", light.constant);
    setVec3("pointLights[" + arrIndex + "].linear", light.linear);
    setVec3("pointLights[" + arrIndex + "].quadratic", light.quadratic);
}

void Shader::setInt(const std::string &name, int v) {
    glUniform1i(location(name), v);
}

void Shader::setFloat(const std::string &name, float v) {
    glUniform1f(location(name), v);
}


void Shader::setVec2(const std::string &name, glm::vec2 v) {
    glUniform2f(location(name), v.x, v.y);
}

void Shader::setVec2(const std::string &name, float x, float y) {
    glUniform2f(location(name), x, y);
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

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) {
    glUniform4f(location(name), x, y, z, w);
}


void Shader::setMat4(const std::string &name, glm::mat4 v) {
    glUniformMatrix4fv(location(name), 1, GL_FALSE, glm::value_ptr(v));
}


//Cleanup
Shader::~Shader() {
    glDeleteProgram(handle);
}
