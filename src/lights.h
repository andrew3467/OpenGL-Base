//
// Created by apgra on 3/25/2023.
//

#ifndef OPENGL_BASE_LIGHTS_H
#define OPENGL_BASE_LIGHTS_H

#include <glm/glm.hpp>


struct Light{
    Light(glm::vec3 pos,
          glm::vec3 ambient,
          glm::vec3 diffuse,
          glm::vec3 specular)
          : position(pos), ambient(ambient), diffuse(diffuse), specular(specular){

    }
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct PointLight : public Light {
    PointLight(glm::vec3 pos,
               glm::vec3 ambient,
               glm::vec3 diffuse,
               glm::vec3 specular,
               float constant,
               float linear,
               float quadratic)
            : Light(pos, ambient, diffuse, specular), constant(constant), linear(linear), quadratic(quadratic) {

    }

public:
    float constant;
    float linear;
    float quadratic;
};

#endif //OPENGL_BASE_LIGHTS_H
