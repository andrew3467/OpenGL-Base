//
// Created by Andrew Graser on 2/26/2023.
//

#include "Shader.h"

#include "engine/ErrorManager.h"


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
    GLErrorManager(unsigned int id = glCreateProgram());
    GLErrorManager(glAttachShader(id, vert));
    GLErrorManager(glAttachShader(id, frag));
    if (geometryPath != nullptr) {
        GLErrorManager(glAttachShader(id, geom));
    }
    GLErrorManager(glLinkProgram(id));

    int success;
    char infoLog[512];
    GLErrorManager(glGetProgramiv(id, GL_LINK_STATUS, &success));
    if (!success) {
        GLErrorManager(glGetProgramInfoLog(id, 512, nullptr, infoLog));
        std::cout << "ERROR::SHADER::LINKING_FAILURE\n" << infoLog << "\n";
    }

    //Cleanup
    GLErrorManager(glDeleteShader(vert));
    GLErrorManager(glDeleteShader(frag));
    if (geometryPath != nullptr) {
        GLErrorManager(glDeleteShader(geom));
    }
    return id;
}

unsigned int Shader::createShader(unsigned int SHADER_TYPE, const char *src) {
    if(src == nullptr){
        throw std::runtime_error("ERROR: Shader received null source");
    }
    GLErrorManager(unsigned int shader = glCreateShader(SHADER_TYPE));
    GLErrorManager(glShaderSource(shader, 1, &src, nullptr));
    GLErrorManager(glCompileShader(shader));


    int success;
    char infoLog[512];
    GLErrorManager(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success) {
        GLErrorManager(glGetShaderInfoLog(shader, 512, nullptr, infoLog));
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
    GLErrorManager(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLErrorManager(glUseProgram(0));
}

int Shader::getUniformLocation(const std::string &name) const {
    if(m_UniformCache.find(name) != m_UniformCache.end()){
        return m_UniformCache[name];
    }

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    m_UniformCache[name] = location;
    return location;
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
    GLErrorManager(glUniform1i(getUniformLocation(name), v));
}

void Shader::SetFloat(const std::string &name, float v) {
    GLErrorManager(glUniform1f(getUniformLocation(name), v));
}


void Shader::setVec2(const std::string &name, glm::vec2 v) {
    GLErrorManager(glUniform2f(getUniformLocation(name), v.x, v.y));
}

void Shader::setVec2(const std::string &name, float x, float y) {
    GLErrorManager(glUniform2f(getUniformLocation(name), x, y));
}


void Shader::SetVec3(const std::string &name, glm::vec3 v) {
    GLErrorManager(glUniform3f(getUniformLocation(name), v.x, v.y, v.z));
}

void Shader::SetVec3(const std::string &name, float x, float y, float z) {
    GLErrorManager(glUniform3f(getUniformLocation(name), x, y, z));
}

void Shader::setVec3(const std::string &name, float v) {
    GLErrorManager(glUniform3f(getUniformLocation(name), v, v, v));
}

void Shader::setVec4(const std::string& name, glm::vec4 v) {
    GLErrorManager(glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w));
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) {
    GLErrorManager(glUniform4f(getUniformLocation(name), x, y, z, w));
}


void Shader::SetMat4(const std::string &name, glm::mat4 v) {
    GLErrorManager(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(v)));
}


//Cleanup
Shader::~Shader() {
    GLErrorManager(glDeleteProgram(m_RendererID));
}
