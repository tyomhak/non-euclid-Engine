#pragma once

#include "scene/component.hpp"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>

#include <glm/glm.hpp>

#include <variant>

namespace njin
{

/// Describes the collision shape attached to an entity.
/// Set one of the shape variants before adding a RigidBody.
class Collider : public Component
{
public:
    struct Box     { glm::vec3 half_extent{0.5f}; };
    struct Sphere  { float radius{0.5f}; };
    struct Capsule { float half_height{0.5f}; float radius{0.25f}; };

    using ShapeData = std::variant<Box, Sphere, Capsule>;
    ShapeData shape{Box{}};

    /// Build the Jolt shape from the current variant.
    JPH::RefConst<JPH::Shape> build_jolt_shape() const
    {
        return std::visit([](auto&& s) -> JPH::RefConst<JPH::Shape> {
            using T = std::decay_t<decltype(s)>;
            if constexpr (std::is_same_v<T, Box>)
                return new JPH::BoxShape(JPH::Vec3(s.half_extent.x, s.half_extent.y, s.half_extent.z));
            else if constexpr (std::is_same_v<T, Sphere>)
                return new JPH::SphereShape(s.radius);
            else if constexpr (std::is_same_v<T, Capsule>)
                return new JPH::CapsuleShape(s.half_height, s.radius);
        }, shape);
    }
};

} // namespace njin
