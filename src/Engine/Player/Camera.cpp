#include "Camera.h"

Camera::Camera(
    glm::vec3 position,
    glm::vec3 up,
    float yaw,
    float pitch): 
        Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        MovementSpeed(SPEED), 
        MouseSensitivity(SENSITIVITY), 
        Zoom(ZOOM), 
        fov(FOV), 
        WorldUp(0.0f, 1.0f, 0.0f)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    UpdateCameraVectors();
}


Camera::Camera(
    float posX, float posY, float posZ, 
    float upX, float upY, float upZ, 
    float yaw, float pitch) : 
        Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
        MovementSpeed(SPEED), 
        MouseSensitivity(SENSITIVITY), 
        Zoom(ZOOM), 
        fov(FOV)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    UpdateCameraVectors();
}


void Camera::ProcessKeyboard(MoveDirection direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime / 2;
    float y = Position.y;
    switch (direction) {
    case FORWARD:
        Position += Front * velocity;
        Position.y = y;
        break;
    case BACKWARD:
        Position -= Front * velocity;
        Position.y = y;
        break;
    case UPWARD:
        Move::moveUPWARD(Position, velocity);
        break;
    case DOWNWARD:
        Move::moveDOWNWARD(Position, velocity);
        break;
    case STRAFELEFT:
        Position -= Right * velocity;
        Position.y = y;
        break;
    case STRAFERIGHT:
        Position += Right * velocity;
        Position.y = y;
    default:
        return;
    }
}


void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw -= xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
}


void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}


void Camera::UpdateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}