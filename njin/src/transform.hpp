#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace njin
{

using Vec3 = glm::vec3;
using Mat4 = glm::mat4;

struct Transform
{
    Vec3 position{0.0f};
    Vec3 rotation{0.0f}; // Euler angles in degrees
    Vec3 scale{1.0f};

    Mat4 get_model_matrix() const
    {
        Mat4 model = Mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), Vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(rotation.y), Vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(rotation.z), Vec3(0, 0, 1));
        model = glm::scale(model, scale);
        return model;
    }

    void rotate_by(Vec3 delta_rotation)
    {
        rotation += delta_rotation;
    }

    void move_by(Vec3 delta_position)
    {
        position += delta_position;
    }

    void scale_by(Vec3 delta_scale)
    {
        scale += delta_scale;
    }
};

}; // namespace njin