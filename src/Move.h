#pragma once

#include <glm/glm.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
static enum MoveDirection {
    FORWARD,
    BACKWARD,
    UPWARD,
    DOWNWARD,
    STRAFELEFT,
    STRAFERIGHT
};


static class Move {
public:
    void static moveDOWNWARD(glm::vec3& position, float speed)
    {
        position.y -= speed;
    }

    void static moveUPWARD(glm::vec3& position, float speed)
    {
        position.y += speed;
    }

    void static moveLEFT(glm::vec3& position, float speed)
    {
        position.x -= speed;
    }

    void static moveRIGHT(glm::vec3& position, float speed)
    {
        position.x += speed;
    }

    void static moveFORWARD(glm::vec3& position, float speed)
    {
        position.z -= speed;
    }

    void static moveBACKWARD(glm::vec3& position, float speed)
    {
        position.z += speed;
    }

};