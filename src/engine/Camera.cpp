//
// Created by apgra on 3/19/2023.
//

#include "Camera.h"


Camera::Camera(glm::vec3 pos, int windowWidth, int windowHeight) : lastX(windowWidth / 2.0f), lastY(windowHeight / 2.0f), windowWidth(windowWidth), windowHeight(windowHeight) {

}

void Camera::Move(CameraMoveDir moveDir, float deltaTime) {
    switch(moveDir){
        case Forward:
            camPos += camSpeed * camFront * deltaTime;
            break;
        case Backward:
            camPos -= camSpeed * camFront * deltaTime;
            break;
        case Right:
            camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed * deltaTime;
            break;
        case Left:
            camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed * deltaTime;
            break;
    }
}

void Camera::Rotate(float mouseX, float mouseY, bool cursorEnabled) {
    if (firstMouse)
    {
        lastX = mouseX;
        lastY = mouseY;
        firstMouse = false;
    }

    float xoffset = mouseX - lastX;
    float yoffset = lastY - mouseY;

    lastX = mouseX;
    lastY = mouseY;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camFront = glm::normalize(direction);
}
