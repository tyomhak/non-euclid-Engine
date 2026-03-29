#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/CastResult.h>

#include <memory>
#include <optional>
#include <cstdint>

namespace njin
{

class Entity;

/// Broad-phase layer: non-moving (static) or moving (dynamic/kinematic).
namespace BPLayers
{
    static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
    static constexpr JPH::BroadPhaseLayer MOVING(1);
    static constexpr uint32_t NUM_LAYERS = 2;
}

/// Object layer: static or dynamic.
namespace ObjLayers
{
    static constexpr JPH::ObjectLayer STATIC  = 0;
    static constexpr JPH::ObjectLayer DYNAMIC = 1;
    static constexpr uint32_t NUM_LAYERS = 2;
}

/// Result of a raycast query.
struct RayHit
{
    Entity* entity{nullptr};
    glm::vec3 point{0.0f};
    glm::vec3 normal{0.0f};
    float fraction{0.0f};
};

class PhysicsWorld
{
public:
    PhysicsWorld();
    ~PhysicsWorld();

    // Non-copyable.
    PhysicsWorld(const PhysicsWorld&) = delete;
    PhysicsWorld& operator=(const PhysicsWorld&) = delete;

    /// Step the physics simulation.
    void step(float dt);

    /// Get access to the underlying Jolt PhysicsSystem.
    JPH::PhysicsSystem& system() { return *_physics_system; }
    JPH::BodyInterface& body_interface();

    /// Map a Jolt BodyID to an njin Entity (for raycasting results, etc.).
    void register_body(JPH::BodyID body_id, Entity* entity);
    void unregister_body(JPH::BodyID body_id);
    Entity* entity_for_body(JPH::BodyID body_id) const;

    /// Cast a ray from origin in direction (normalized).
    /// Returns the closest hit within max_distance, or std::nullopt.
    std::optional<RayHit> raycast(const glm::vec3& origin,
                                  const glm::vec3& direction,
                                  float max_distance = 1000.0f) const;

    // --- GLM ↔ Jolt conversions ---
    static JPH::Vec3 to_jolt(const glm::vec3& v) { return JPH::Vec3(v.x, v.y, v.z); }
    static glm::vec3 to_glm(const JPH::Vec3& v)  { return glm::vec3(v.GetX(), v.GetY(), v.GetZ()); }
    static JPH::Quat to_jolt(const glm::quat& q) { return JPH::Quat(q.x, q.y, q.z, q.w); }
    static glm::quat to_glm(const JPH::Quat& q)  { return glm::quat(q.GetW(), q.GetX(), q.GetY(), q.GetZ()); }

private:
    // Jolt subsystems
    std::unique_ptr<JPH::TempAllocatorImpl>    _temp_allocator;
    std::unique_ptr<JPH::JobSystemThreadPool>  _job_system;
    std::unique_ptr<JPH::PhysicsSystem>        _physics_system;

    // Body → Entity mapping
    std::unordered_map<uint32_t, Entity*> _body_entity_map;

    static constexpr int COLLISION_STEPS = 1;
};

} // namespace njin
