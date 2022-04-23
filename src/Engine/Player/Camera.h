#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Move.h"


// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 15.0f;
const float SENSITIVITY = 0.05f;
const float ZOOM = 45.0f;
const float FOV = 90.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW, 
        float pitch = PITCH);

    // constructor with scalar values
    Camera(float posX, float posY, float posZ, 
        float upX, float upY, float upZ, 
        float yaw, float pitch);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() const { return lookAt(Position, Position + Front, Up); }

    glm::vec3 GetPosition() const { return Position; }

    glm::vec3 GetFront() const { return Front; }

    glm::vec3 GetUp() const{ return Up; }

    float GetFOV() const{ return fov; }


    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(MoveDirection direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

    //glm::mat4 GetInvertedCamera(float y) {
    //    // returns the inverted camera matrix
    //    return glm::mat4(1.0f);
    //}

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void UpdateCameraVectors();

public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float fov;
};