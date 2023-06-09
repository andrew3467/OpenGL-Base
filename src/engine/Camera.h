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

    int windowWidth;
    int windowHeight;

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
    Camera();
    Camera(glm::vec3 pos, int windowWidth, int windowHeight);

    void Move(CameraMoveDir moveDir, float deltaTime);
    void Rotate(float mouseX, float mouseY, bool cursorEnabled = false);

    inline float GetYaw() const { return yaw;}
    inline float GetPitch() const { return pitch;}

    inline glm::mat4 viewProjection() const {return projection() * view();}
    inline glm::mat4 projection() const {return glm::perspective(glm::radians(60.0f),
                                                                 (float)windowWidth / (float)windowHeight,0.1f, 100.0f);}
    inline glm::mat4 view() const {return glm::lookAt(camPos, center(), camUp);}
    inline glm::vec3 position() const {return camPos;}
    inline glm::vec3 front() const {return camFront;}
    inline glm::vec3 center() const {return camPos + camFront;}
    inline glm::vec3 cameraUp() const {return camUp;}
};



#endif //OPENGL_BASE_CAMERA_H
