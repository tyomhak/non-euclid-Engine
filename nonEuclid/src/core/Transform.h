#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
    Transform()
        : position(1.0f)
        , rotation(1.0f)
        , scale(1.0f)
    {}
    Transform(const Transform& o) = default;

    glm::mat4 position;
    glm::mat4 rotation;
    glm::mat4 scale;

    glm::mat4 get_transform_mat() const
    {
        return position * rotation * scale;
    }

    void set_position(const glm::vec3& pos)
    {
        position = glm::translate(glm::mat4(1.0f), pos);
    }
    void translate(const glm::vec3& vec)
    {
        position = glm::translate(position, vec);
    }
    void rotate(float degrees, const glm::vec3& axis)
    {
        rotation = glm::rotate(glm::radians(degrees), axis);
    }

    void set_scale(const glm::vec3& s)
    {
        scale = glm::scale(glm::mat4(1.0f), s);
    }
    void scale_by(const glm::vec3& s)
    {
        scale = glm::scale(scale, s);
    }

};