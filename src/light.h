//
// Created by apgra on 3/25/2023.
//

#ifndef OPENGL_BASE_LIGHT_H
#define OPENGL_BASE_LIGHT_H

#include <glm/glm.hpp>


class Light{
public:
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif //OPENGL_BASE_LIGHT_H
