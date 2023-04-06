//
// Created by Andrew Graser on 4/3/2023.
//

#ifndef OPENGL_BASE_OBJECTDATA_H
#define OPENGL_BASE_OBJECTDATA_H

#include <vector>
#include <string>
#include "glm/vec3.hpp"
#include "engine/Lights.h"

std::vector<std::string> faces =
        {
                "../../resources/textures/skybox/right.jpg",
                "../../resources/textures/skybox/left.jpg",
                "../../resources/textures/skybox/top.jpg",
                "../../resources/textures/skybox/bottom.jpg",
                "../../resources/textures/skybox/front.jpg",
                "../../resources/textures/skybox/back.jpg"
        };

GLuint cubeIndices[] = {
        0, 1, 5,  5, 1, 6,
        1, 2, 6,  6, 2, 7,
        2, 3, 7,  7, 3, 8,
        3, 4, 8,  8, 4, 9,
        10,11, 0,  0,11, 1,
        5, 6,12, 12, 6,13
};

float cubeVertices[] = {
        -1,-1,-1, 0, 0,
        1,-1,-1, 1, 0,
        1, 1,-1, 2, 0,
        -1, 1,-1, 3, 0,
        -1,-1,-1, 4, 0,

        -1,-1, 1, 0, 1,
        1,-1, 1, 1, 1,
        1, 1, 1, 2, 1,
        -1, 1, 1, 3, 1,
        -1,-1, 1, 4, 1,

        -1, 1,-1, 0,-1,
        1, 1,-1, 1,-1,

        -1, 1, 1, 0, 2,
        1, 1, 1, 1, 2
};

float planeVertices[48] = {
        // positions                // normals                          // texcoords
        -0.5, -0.5f,  -0.5,  0.0f, 1.0f, 0.0f,  1.0f,  1.0f,             //0
        0.5, -0.5f,  -0.5,  0.0f, 1.0f, 0.0f,   1.0f,  0.0f,      //1
        0.5, -0.5f, 0.5,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,     //2
        -0.5, -0.5f, 0.5,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f        //3
};

unsigned int planeIndices[6] = {
        0,1,2,
        2,3,0
};

glm::vec3 cameraPosition = glm::vec3(0.0f, 1.0f, -4.0f);

int numPointLights = 4;
std::vector<PointLight> pointLights = {
        PointLight(
                glm::vec3(-2.0f, 1.0f, -2.0f),
                glm::vec3(0.25f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                0.0f,
                0.0f,
                0.0f
        ),
        PointLight(
                glm::vec3(2.0f, 1.0f, 2.0f),
                glm::vec3(0.50f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                0.0f,
                0.0f,
                0.0f
        ),
        PointLight(
                glm::vec3 (-2.0f, 1.0f, 2.0f),
                glm::vec3(0.75f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                0.0f,
                0.0f,
                0.0f
        ),
        PointLight(
                glm::vec3 (2.0f, 1.0f, -2.0f),
                glm::vec3(1.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                0.0f,
                0.0f,
                0.0f
        )
};

std::vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f,1.5f, 0.0f)
};

std::vector<glm::vec3> cubeRotations = {
        glm::vec3(45.0f, 0.0f, 30.0f)
};

#endif //OPENGL_BASE_OBJECTDATA_H
