#ifndef AABB_COLLISION
#define AABB_COLLISION

#include "IncludeHeaders.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Object.h"

class CollisionHandler {
public:
    CollisionHandler() {};

    // intersection check of aabb with point
    static bool check_collision(const Camera camera, const BoundaryBox box)
    {
        return (camera.Position.x >= box.getMinPoint().x && camera.Position.x <= box.getMaxPoint().x)
            && (camera.Position.y >= box.getMinPoint().y && camera.Position.y <= box.getMaxPoint().y)
            && (camera.Position.z >= box.getMinPoint().z && camera.Position.z <= box.getMaxPoint().z);
    }

    // intersection check of aabb with point
    static bool check_collision(const Camera camera, const Object object)
    {
        return check_collision(camera, object.getBoundaryBox());
    }


    // intersection check of aabb with aabb
    static bool check_collision(const BoundaryBox box1, const BoundaryBox box2)
    {
        return (box1.getMinPoint().x <= box2.getMaxPoint().x && box1.getMaxPoint().x >= box2.getMinPoint().x)
            && (box1.getMinPoint().y <= box2.getMaxPoint().y && box1.getMaxPoint().y >= box2.getMinPoint().y)
            && (box1.getMinPoint().z <= box2.getMaxPoint().z && box1.getMaxPoint().z >= box2.getMinPoint().z);
    }

    // intersection check of aabb with aabb
    static bool check_collision(const Object object1, const Object object2)
    {
        return check_collision(object1.getBoundaryBox(), object2.getBoundaryBox());
    }

};

#endif  //!AABB_COLLISION