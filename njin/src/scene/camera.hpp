#pragma once

#include "component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace njin
{

class Camera : public Component
{
public:
    float fov{60.0f};         // vertical FOV in degrees
    float near_plane{0.1f};
    float far_plane{100.0f};

    // Euler angles (degrees) — temporary convenience until a proper FPS controller exists.
    float yaw{-90.0f};
    float pitch{0.0f};

    glm::vec3 front() const
    {
        glm::vec3 f;
        f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        f.y = sin(glm::radians(pitch));
        f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        return glm::normalize(f);
    }

    glm::vec3 right() const
    {
        return glm::normalize(glm::cross(front(), glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    glm::vec3 up() const
    {
        return glm::normalize(glm::cross(right(), front()));
    }

    glm::mat4 view_matrix(const glm::vec3& position) const
    {
        return glm::lookAt(position, position + front(), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::mat4 projection_matrix(float aspect_ratio) const
    {
        return glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane);
    }
};

} // namespace njin
