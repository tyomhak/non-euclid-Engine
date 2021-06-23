#ifndef AABB_COLLISION
#define AABB_COLLISION

#include "IncludeHeaders.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Ray.h"
#include "Camera.h"
#include "Object.h"
#include "Player.h"

class CollisionHandler {
public:
    CollisionHandler() {};

    // intersection check of aabb with point
    static bool check_collision(const Camera camera, const BoundaryBox box)
    {
        return (camera.getPosition().x >= box.GetMinPoint().x && camera.getPosition().x <= box.GetMaxPoint().x)
            && (camera.getPosition().y >= box.GetMinPoint().y && camera.getPosition().y <= box.GetMaxPoint().y)
            && (camera.getPosition().z >= box.GetMinPoint().z && camera.getPosition().z <= box.GetMaxPoint().z);
    }

    // intersection check of aabb with point
    static bool check_collision(const Camera camera, const Object object)
    {
        return check_collision(camera, object.GetBoundaryBox());
    }

    // intersection check of aabb with point
    static bool check_collision(const Player player, const Object object)
    {
        return check_collision(player.GetBoundaryBox(), object.GetBoundaryBox());
    }

    // intersection check of aabb with aabb
    static bool check_collision(const BoundaryBox box1, const BoundaryBox box2)
    {
        return (box1.GetMinPoint().x <= box2.GetMaxPoint().x && box1.GetMaxPoint().x >= box2.GetMinPoint().x)
            && (box1.GetMinPoint().y <= box2.GetMaxPoint().y && box1.GetMaxPoint().y >= box2.GetMinPoint().y)
            && (box1.GetMinPoint().z <= box2.GetMaxPoint().z && box1.GetMaxPoint().z >= box2.GetMinPoint().z);
    }

    // intersection check of aabb with aabb
    static bool check_collision(const Object object1, const Object object2)
    {
        return check_collision(object1.GetBoundaryBox(), object2.GetBoundaryBox());
    }

    static bool check_collision(const Ray ray, const Object object, float &t)
    {
        BoundaryBox box = object.GetBoundaryBox();
        glm::vec3 min = box.GetMinPoint();
        glm::vec3 max = box.GetMaxPoint();

        glm::vec3 orig = ray.getOrigin();
        glm::vec3 dir = ray.getDirection();

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

private:
    // deprecated
    static bool check_radius_collision(const Player player, const Object object) 
    {
        float distance_from_centers = glm::distance(player.GetBoundaryBox().GetCenterPoint(), object.GetBoundaryBox().GetCenterPoint());
        float distance_from_edges = distance_from_centers
                                        - (distance(player.GetBoundaryBox().GetMinPoint(), player.GetBoundaryBox().GetMaxPoint()) / 2)
                                        - (distance(object.GetBoundaryBox().GetMinPoint(), object.GetBoundaryBox().GetMaxPoint()) / 2);

        return player.GetRadius() > distance_from_edges;
    }
};

#endif  //!AABB_COLLISION