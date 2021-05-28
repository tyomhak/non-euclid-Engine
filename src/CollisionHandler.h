#ifndef AABB_COLLISION
#define AABB_COLLISION

#include "IncludeHeaders.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Object.h"
#include "Player.h"

class CollisionHandler {
public:
    CollisionHandler() {};

    // intersection check of aabb with point
    static bool check_collision(const Camera camera, const BoundaryBox box)
    {
        return (camera.getPosition().x >= box.getMinPoint().x && camera.getPosition().x <= box.getMaxPoint().x)
            && (camera.getPosition().y >= box.getMinPoint().y && camera.getPosition().y <= box.getMaxPoint().y)
            && (camera.getPosition().z >= box.getMinPoint().z && camera.getPosition().z <= box.getMaxPoint().z);
    }

    // intersection check of aabb with point
    static bool check_collision(const Camera camera, const Object object)
    {
        return check_collision(camera, object.getBoundaryBox());
    }

    // intersection check of aabb with point
    static bool check_collision(const Player player, const Object object)
    {
        return check_collision(player.getBoundaryBox(), object.getBoundaryBox());
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


private:
    // deprecated
    static bool check_radius_collision(const Player player, const Object object) 
    {
        float distance_from_centers = glm::distance(player.getBoundaryBox().getCenterPoint(), object.getBoundaryBox().getCenterPoint());
        float distance_from_edges = distance_from_centers
                                        - (distance(player.getBoundaryBox().getMinPoint(), player.getBoundaryBox().getMaxPoint()) / 2)
                                        - (distance(object.getBoundaryBox().getMinPoint(), object.getBoundaryBox().getMaxPoint()) / 2);

        return player.getRadius() > distance_from_edges;
    }
};

#endif  //!AABB_COLLISION