//
// Created by Andrew Graser on 2/26/2023.
//

#include "Shader.h"


Shader::Shader() : m_RendererID(0) {

}

Shader::Shader(const char *vertPath, const char *fragPath, const char* geometryPath) {
    m_RendererID = createShaderProgram(vertPath, fragPath, geometryPath);
}

unsigned int Shader::createShaderProgram(const char *vertPath, const char *fragPath, const char* geometryPath) {
    unsigned int vert, frag, geom;
    vert = createShader(GL_VERTEX_SHADER, readSourceFile(vertPath).c_str());
    frag = createShader(GL_FRAGMENT_SHADER, readSourceFile(fragPath).c_str());
    if (geometryPath != nullptr) {
        geom = createShader(GL_GEOMETRY_SHADER, readSourceFile(geometryPath).c_str());
    }
    GLCall(unsigned int id = glCreateProgram());
    GLCall(glAttachShader(id, vert));
    GLCall(glAttachShader(id, frag));
    if (geometryPath != nullptr) {
        GLCall(glAttachShader(id, geom));
    }
    GLCall(glLinkProgram(id));

    int success;
    char infoLog[512];
    GLCall(glGetProgramiv(id, GL_LINK_STATUS, &success));
    if (!success) {
        GLCall(glGetProgramInfoLog(id, 512, nullptr, infoLog));
        std::cout << "ERROR::SHADER::LINKING_FAILURE\n" << infoLog << "\n";
    }

    //Cleanup
    GLCall(glDeleteShader(vert));
    GLCall(glDeleteShader(frag));
    if (geometryPath != nullptr) {
        GLCall(glDeleteShader(geom));
    }
    return id;
}

unsigned int Shader::createShader(unsigned int SHADER_TYPE, const char *src) {
    if(src == nullptr){
        throw std::runtime_error("ERROR: Shader received null source");
    }
    GLCall(unsigned int shader = glCreateShader(SHADER_TYPE));
    GLCall(glShaderSource(shader, 1, &src, nullptr));
    GLCall(glCompileShader(shader));


    int success;
    char infoLog[512];
    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success) {
        GLCall(glGetShaderInfoLog(shader, 512, nullptr, infoLog));
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

void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

int Shader::location(const std::string& n) const {
    GLCall(return glGetUniformLocation(m_RendererID, n.c_str()));
}



void Shader::SetPointLight(const PointLight &light, const std::string& arrIndex) {
    SetVec3("pointLights[" + arrIndex + "].position", light.position);

    SetVec3("pointLights[" + arrIndex + "].ambient", light.ambient);
    SetVec3("pointLights[" + arrIndex + "].diffuse", light.diffuse);
    SetVec3("pointLights[" + arrIndex + "].specular", light.specular);

    setVec3("pointLights[" + arrIndex + "].constant", light.constant);
    setVec3("pointLights[" + arrIndex + "].linear", light.linear);
    setVec3("pointLights[" + arrIndex + "].quadratic", light.quadratic);
}

void Shader::SetInt(const std::string &name, int v) {
    GLCall(glUniform1i(location(name), v));
}

void Shader::SetFloat(const std::string &name, float v) {
    GLCall(glUniform1f(location(name), v));
}


void Shader::setVec2(const std::string &name, glm::vec2 v) {
    GLCall(glUniform2f(location(name), v.x, v.y));
}

void Shader::setVec2(const std::string &name, float x, float y) {
    GLCall(glUniform2f(location(name), x, y));
}


void Shader::SetVec3(const std::string &name, glm::vec3 v) {
    GLCall(glUniform3f(location(name), v.x, v.y, v.z));
}

void Shader::SetVec3(const std::string &name, float x, float y, float z) {
    GLCall(glUniform3f(location(name), x, y, z));
}

void Shader::setVec3(const std::string &name, float v) {
    GLCall(glUniform3f(location(name), v, v, v));
}

void Shader::setVec4(const std::string& name, glm::vec4 v) {
    GLCall(glUniform4f(location(name), v.x, v.y, v.z, v.w));
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) {
    GLCall(glUniform4f(location(name), x, y, z, w));
}


void Shader::SetMat4(const std::string &name, glm::mat4 v) {
    GLCall(glUniformMatrix4fv(location(name), 1, GL_FALSE, glm::value_ptr(v)));
}


//Cleanup
Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}
