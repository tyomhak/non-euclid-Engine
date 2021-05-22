#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Camera
{
public:
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
            float _yaw = -90.0f,
            float _pitch = -90.0f):
    cameraPos(pos),
    cameraFront(front),
    cameraUp(0.0f, 1.0f, 0.0f),
    cameraSpeed(10.0f),
    yaw(_yaw),
    pitch(_pitch)
    {};

    glm::mat4 GetView() { return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); }

    glm::vec3 GetPosition() { return cameraPos; }
    glm::vec3 GetFront() { return cameraFront; }

    float GetYaw() { return yaw; }
    float GetPitch() { return pitch; }

    void SetPosition(glm::vec3 _pos) { cameraPos = _pos; }
    void SetFront(glm::vec3 _front) { cameraFront = _front; }

    void Walk(float moveSpeed) {    cameraPos += moveSpeed * cameraFront;  } 
    void Walk() {   return Walk(cameraSpeed);   }
    
    void WalkBack(float moveSpeed) { return Walk(-moveSpeed); }
    void WalkBack() { return WalkBack(cameraSpeed); }

    void StrafeRight(float moveSpeed) { cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * moveSpeed; }
    void StrafeRight() { return StrafeRight(cameraSpeed); }

    void StrafeLeft(float moveSpeed) { StrafeRight(-moveSpeed); }
    void StrafeLeft() { return StrafeLeft(cameraSpeed); }

    void MoveUp(float moveSpeed) { cameraPos += moveSpeed * cameraUp;}
    void MoveUp() { return MoveUp(cameraSpeed); }

    void MoveDown(float moveSpeed) { return MoveUp(-moveSpeed); }
    void MoveDown() { return MoveDown(cameraSpeed); }

    float GetCameraSpeed() { return cameraSpeed; }
    void SetCameraSpeed(float newSpeed) { cameraSpeed = newSpeed; }

    void MoveMouse(float xoffset, float yoffset)
    {
        yaw += xoffset;
        pitch += yoffset;

        if (pitch >= 89.0f)
            pitch = 89.0f;
        else if (pitch <= -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
    }

private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float yaw;
    float pitch;
    float cameraSpeed;
};