#pragma once

#include "scene/component.hpp"
#include "scene/entity.hpp"
#include "physics/collider.hpp"
#include "physics/physics_world.hpp"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace njin
{

enum class BodyType
{
    Static,
    Kinematic,
    Dynamic
};

/// Component that creates and syncs a Jolt physics body.
/// Requires a Collider component on the same entity.
/// Call init() after adding both Collider and RigidBody to create the Jolt body.
class RigidBody : public Component
{
public:
    BodyType body_type{BodyType::Dynamic};
    float    mass{1.0f};
    float    friction{0.5f};
    float    restitution{0.3f};

    /// Create the Jolt body. Must be called after the entity has a Collider and
    /// after the PhysicsWorld exists.
    void init(PhysicsWorld& world)
    {
        _world = &world;
        auto* entity = owner();
        if (!entity) return;

        auto* collider = entity->get_component<Collider>();
        if (!collider) return;

        JPH::RefConst<JPH::Shape> shape = collider->build_jolt_shape();

        auto& tf = entity->transform;
        JPH::Vec3 pos = PhysicsWorld::to_jolt(tf.position);

        // Convert Euler angles (degrees) → quaternion.
        glm::quat q = glm::quat(glm::radians(tf.rotation));
        JPH::Quat rot = PhysicsWorld::to_jolt(q);

        JPH::EMotionType motion;
        JPH::ObjectLayer layer;
        switch (body_type)
        {
            case BodyType::Static:
                motion = JPH::EMotionType::Static;
                layer  = ObjLayers::STATIC;
                break;
            case BodyType::Kinematic:
                motion = JPH::EMotionType::Kinematic;
                layer  = ObjLayers::DYNAMIC;
                break;
            default:
                motion = JPH::EMotionType::Dynamic;
                layer  = ObjLayers::DYNAMIC;
                break;
        }

        JPH::BodyCreationSettings settings(shape, pos, rot, motion, layer);
        settings.mFriction    = friction;
        settings.mRestitution = restitution;

        if (body_type == BodyType::Dynamic && mass > 0.0f)
        {
            settings.mOverrideMassProperties = JPH::EOverrideMassProperties::CalculateInertia;
            settings.mMassPropertiesOverride.mMass = mass;
        }
        auto& bi = world.body_interface();
        _body_id = bi.CreateAndAddBody(settings, JPH::EActivation::Activate);

        world.register_body(_body_id, entity);
    }

    /// Sync entity transform ← Jolt body (call after physics step).
    void sync_from_physics()
    {
        if (!_world || _body_id.IsInvalid()) return;
        if (body_type == BodyType::Static) return;

        auto& bi = _world->body_interface();
        JPH::Vec3 pos = bi.GetPosition(_body_id);
        JPH::Quat rot = bi.GetRotation(_body_id);

        auto* entity = owner();
        if (!entity) return;

        entity->transform.position = PhysicsWorld::to_glm(pos);
        glm::quat q = PhysicsWorld::to_glm(rot);
        entity->transform.rotation = glm::degrees(glm::eulerAngles(q));
    }

    /// Sync Jolt body ← entity transform (for kinematic bodies or manual repositioning).
    void sync_to_physics()
    {
        if (!_world || _body_id.IsInvalid()) return;

        auto* entity = owner();
        if (!entity) return;

        auto& tf = entity->transform;
        glm::quat q = glm::quat(glm::radians(tf.rotation));

        auto& bi = _world->body_interface();
        bi.SetPositionAndRotation(_body_id,
            PhysicsWorld::to_jolt(tf.position),
            PhysicsWorld::to_jolt(q),
            JPH::EActivation::Activate);
    }

    /// Apply an impulse (world space) to the body's center of mass.
    void apply_impulse(const glm::vec3& impulse)
    {
        if (!_world || _body_id.IsInvalid()) return;
        _world->body_interface().AddImpulse(_body_id, PhysicsWorld::to_jolt(impulse));
    }

    /// Apply a force (world space) to the body's center of mass.
    void apply_force(const glm::vec3& force)
    {
        if (!_world || _body_id.IsInvalid()) return;
        _world->body_interface().AddForce(_body_id, PhysicsWorld::to_jolt(force));
    }

    JPH::BodyID jolt_body_id() const { return _body_id; }

    void on_detach() override
    {
        if (_world && !_body_id.IsInvalid())
        {
            _world->unregister_body(_body_id);
            _world->body_interface().RemoveBody(_body_id);
            _world->body_interface().DestroyBody(_body_id);
            _body_id = JPH::BodyID();
        }
    }

private:
    PhysicsWorld* _world{nullptr};
    JPH::BodyID  _body_id;
};

} // namespace njin
