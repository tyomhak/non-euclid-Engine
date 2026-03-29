// Jolt requires this header order: Jolt.h first, then everything else.
#include <Jolt/Jolt.h>

#include "physics_world.hpp"

#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/CastResult.h>
#include <Jolt/Physics/Collision/NarrowPhaseQuery.h>

#include <iostream>
#include <thread>
#include <cstdarg>

namespace njin
{

// --- Jolt callback implementations (minimal) ---

// BroadPhaseLayerInterface: maps ObjectLayer → BroadPhaseLayer.
class BPLayerInterface final : public JPH::BroadPhaseLayerInterface
{
public:
    uint32_t GetNumBroadPhaseLayers() const override { return BPLayers::NUM_LAYERS; }

    JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer layer) const override
    {
        return (layer == ObjLayers::STATIC) ? BPLayers::NON_MOVING : BPLayers::MOVING;
    }

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
    const char* GetBroadPhaseLayerName(JPH::BroadPhaseLayer layer) const override
    {
        if (layer == BPLayers::NON_MOVING) return "NON_MOVING";
        if (layer == BPLayers::MOVING) return "MOVING";
        return "UNKNOWN";
    }
#endif
};

// ObjectVsBroadPhaseLayerFilter: should moving objects collide with this broad phase layer?
class ObjVsBPLayerFilter final : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:
    bool ShouldCollide(JPH::ObjectLayer obj, JPH::BroadPhaseLayer bp) const override
    {
        if (obj == ObjLayers::STATIC)
            return bp == BPLayers::MOVING;      // statics only vs moving
        return true;                             // dynamics collide with everything
    }
};

// ObjectLayerPairFilter: which object layers collide with each other?
class ObjLayerPairFilter final : public JPH::ObjectLayerPairFilter
{
public:
    bool ShouldCollide(JPH::ObjectLayer a, JPH::ObjectLayer b) const override
    {
        if (a == ObjLayers::STATIC && b == ObjLayers::STATIC)
            return false;    // statics never collide with statics
        return true;
    }
};

// File-scope singleton instances for Jolt callbacks.
static BPLayerInterface     s_bp_layer_interface;
static ObjVsBPLayerFilter   s_obj_vs_bp_filter;
static ObjLayerPairFilter   s_obj_layer_pair_filter;

// Jolt trace callback
static void JoltTraceImpl(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char buf[1024];
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    std::cerr << "[Jolt] " << buf << std::endl;
}

#ifdef JPH_ENABLE_ASSERTS
static bool JoltAssertFailed(const char* expression, const char* message, const char* file, unsigned int line)
{
    std::cerr << "[Jolt Assert] " << file << ":" << line << ": " << expression;
    if (message) std::cerr << " — " << message;
    std::cerr << std::endl;
    return true; // break into debugger
}
#endif

// --- PhysicsWorld implementation ---

PhysicsWorld::PhysicsWorld()
{
    // Register Jolt types (once).
    JPH::RegisterDefaultAllocator();
    JPH::Trace = JoltTraceImpl;
#ifdef JPH_ENABLE_ASSERTS
    JPH::AssertFailed = JoltAssertFailed;
#endif
    JPH::Factory::sInstance = new JPH::Factory();
    JPH::RegisterTypes();

    _temp_allocator = std::make_unique<JPH::TempAllocatorImpl>(10 * 1024 * 1024); // 10 MB

    unsigned int num_threads = std::max(1u, std::thread::hardware_concurrency() - 1);
    _job_system = std::make_unique<JPH::JobSystemThreadPool>(
        JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, static_cast<int>(num_threads));

    constexpr uint32_t max_bodies        = 4096;
    constexpr uint32_t num_body_mutexes  = 0; // auto
    constexpr uint32_t max_body_pairs    = 4096;
    constexpr uint32_t max_contact_constraints = 2048;

    _physics_system = std::make_unique<JPH::PhysicsSystem>();
    _physics_system->Init(max_bodies, num_body_mutexes, max_body_pairs, max_contact_constraints,
                          s_bp_layer_interface, s_obj_vs_bp_filter, s_obj_layer_pair_filter);

    _physics_system->SetGravity(JPH::Vec3(0.0f, -9.81f, 0.0f));
}

PhysicsWorld::~PhysicsWorld()
{
    _physics_system.reset();
    _job_system.reset();
    _temp_allocator.reset();

    JPH::UnregisterTypes();
    delete JPH::Factory::sInstance;
    JPH::Factory::sInstance = nullptr;
}

void PhysicsWorld::step(float dt)
{
    _physics_system->Update(dt, COLLISION_STEPS, _temp_allocator.get(), _job_system.get());
}

JPH::BodyInterface& PhysicsWorld::body_interface()
{
    return _physics_system->GetBodyInterfaceNoLock();
}

void PhysicsWorld::register_body(JPH::BodyID body_id, Entity* entity)
{
    _body_entity_map[body_id.GetIndexAndSequenceNumber()] = entity;
}

void PhysicsWorld::unregister_body(JPH::BodyID body_id)
{
    _body_entity_map.erase(body_id.GetIndexAndSequenceNumber());
}

Entity* PhysicsWorld::entity_for_body(JPH::BodyID body_id) const
{
    auto it = _body_entity_map.find(body_id.GetIndexAndSequenceNumber());
    return (it != _body_entity_map.end()) ? it->second : nullptr;
}

std::optional<RayHit> PhysicsWorld::raycast(const glm::vec3& origin,
                                            const glm::vec3& direction,
                                            float max_distance) const
{
    JPH::RRayCast ray;
    ray.mOrigin    = to_jolt(origin);
    ray.mDirection = to_jolt(direction) * max_distance;

    JPH::RayCastResult result;
    bool hit = _physics_system->GetNarrowPhaseQuery().CastRay(ray, result);
    if (!hit)
        return std::nullopt;

    RayHit out;
    out.fraction = result.mFraction;
    out.point    = origin + direction * (max_distance * result.mFraction);
    out.entity   = entity_for_body(result.mBodyID);

    // Get surface normal at hit point.
    JPH::BodyLockRead lock(_physics_system->GetBodyLockInterface(), result.mBodyID);
    if (lock.Succeeded())
    {
        JPH::Vec3 normal = lock.GetBody().GetWorldSpaceSurfaceNormal(result.mSubShapeID2,
                                                                      ray.GetPointOnRay(result.mFraction));
        out.normal = to_glm(normal);
    }

    return out;
}

} // namespace njin
