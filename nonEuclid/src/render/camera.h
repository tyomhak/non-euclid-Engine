#pragma once

#include "render_target.h"

namespace render
{

struct Camera
{
    int render_priority = 0;
    ID<RenderTarget> custom_render_target{ ID<RenderTarget>::uninitialized() };

    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    float fov = 90.0f; // degrees
    float near = 0.1f;
    float far = 100.0f;
    float aspect_ratio = 4.f / 3.f;

    glm::mat4 GetViewMat()
    {
        return glm::lookAt(
            position,
            target,
            up
        );
    }

    glm::mat4 GetProjectionMat() const
    {
        return glm::perspective(
            glm::radians(fov),
            aspect_ratio,
            near,
            far
        );
    }
};


}