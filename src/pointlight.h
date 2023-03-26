//
// Created by apgra on 3/25/2023.
//

#ifndef OPENGL_BASE_POINTLIGHT_H
#define OPENGL_BASE_POINTLIGHT_H

#include <light.h>

class PointLight : public Light {

public:
    PointLight() : constant(0), linear(0), quadratic(0) {

    }

private:
    float constant;
    float linear;
    float quadratic;
};

#endif //OPENGL_BASE_POINTLIGHT_H
