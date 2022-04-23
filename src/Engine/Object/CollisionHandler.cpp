#include "CollisionHandler.h"


bool CollisionHandler::CheckCollision(const Camera camera, const BoundaryBox box)
{
    return (camera.GetPosition().x >= box.GetMinPoint().x && camera.GetPosition().x <= box.GetMaxPoint().x)
        && (camera.GetPosition().y >= box.GetMinPoint().y && camera.GetPosition().y <= box.GetMaxPoint().y)
        && (camera.GetPosition().z >= box.GetMinPoint().z && camera.GetPosition().z <= box.GetMaxPoint().z);
}

bool CollisionHandler::CheckCollision(const Camera camera, const Object object)
{
    return CheckCollision(camera, object.GetBoundaryBox());
}


bool CollisionHandler::CheckCollision(const Player player, const Object object)
{
    return CheckCollision(player.GetBoundaryBox(), object.GetBoundaryBox());
}


bool CollisionHandler::CheckCollision(const BoundaryBox box1, const BoundaryBox box2)
{
    return (box1.GetMinPoint().x <= box2.GetMaxPoint().x && box1.GetMaxPoint().x >= box2.GetMinPoint().x)
        && (box1.GetMinPoint().y <= box2.GetMaxPoint().y && box1.GetMaxPoint().y >= box2.GetMinPoint().y)
        && (box1.GetMinPoint().z <= box2.GetMaxPoint().z && box1.GetMaxPoint().z >= box2.GetMinPoint().z);
}


bool CollisionHandler::CheckCollision(const Object object1, const Object object2)
{
    return CheckCollision(object1.GetBoundaryBox(), object2.GetBoundaryBox());
}


bool CollisionHandler::CheckCollision(const Ray ray, const Object object, float& t)
{
    BoundaryBox box = object.GetBoundaryBox();
    glm::vec3 min = box.GetMinPoint();
    glm::vec3 max = box.GetMaxPoint();

    glm::vec3 orig = ray.GetOrigin();
    glm::vec3 dir = ray.GetDirection();

    float tmin = (min.x - orig.x) / dir.x;
    float tmax = (max.x - orig.x) / dir.x;

    if (tmin > tmax) swap(tmin, tmax);

    float tymin = (min.y - orig.y) / dir.y;
    float tymax = (max.y - orig.y) / dir.y;

    if (tymin > tymax) swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (min.z - orig.z) / dir.z;
    float tzmax = (max.z - orig.z) / dir.z;

    if (tzmin > tzmax) swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    if (tmin < 0)
    {
        if (tmax < 0)
        {
            return false;
        }
        tmin = tmax;
    }

    t = tmin;

    return true;
}