//
// Created by apgra on 3/19/2023.
//

#ifndef OPENGL_BASE_CAMERA_H
#define OPENGL_BASE_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum CameraMoveDir{
    Forward = 0,
    Backward = 1,
    Right = 2,
    Left = 3
};

class Camera{
private:
    bool firstMouse = true;

    const float sensitivity = 0.1f;
    float yaw = -90.0f;
    float pitch = 0.0f;


    float lastX;
    float lastY;
    const float camSpeed = 10.0f;

    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);

    glm::vec3 camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 camDir = glm::normalize(camPos - camTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 camRight = glm::normalize(glm::cross(up, camDir));
    glm::vec3 camUp = glm::cross(camDir, camRight);

public:
    Camera(glm::vec3 pos, int windowWidth, int windowHeight);

    void move(CameraMoveDir moveDir, float deltaTime);
    void rotate(float mouseX, float mouseY);

    inline float getYaw() const { return yaw;}
    inline float getPitch() const { return pitch;}
    inline glm::mat4 projection(int w, int h) const {return glm::perspective(glm::radians(60.0f), (float)w / (float)h, 0.1f, 100.0f);}
    inline glm::mat4 view() const {return glm::lookAt(camPos, camPos + camFront, camUp);}
    inline glm::vec3 position() const {return camPos;}
    inline glm::vec3 front() const {return camFront;}
};



#endif //OPENGL_BASE_CAMERA_H
