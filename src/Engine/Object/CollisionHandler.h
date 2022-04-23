#pragma once

//#include "IncludeHeaders.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Ray.h"
//#include "Camera.h"
#include "Object.h"
#include "Player.h"

class CollisionHandler {
public:
    CollisionHandler() {};

    // intersection check of aabb with point
    static bool CheckCollision(const Camera camera, const BoundaryBox box);

    // intersection check of aabb with point
    static bool CheckCollision(const Camera camera, const Object object);

    // intersection check of aabb with point
    static bool CheckCollision(const Player player, const Object object);

    // intersection check of aabb with aabb
    static bool CheckCollision(const BoundaryBox box1, const BoundaryBox box2);

    // intersection check of aabb with aabb
    static bool CheckCollision(const Object object1, const Object object2);

    static bool CheckCollision(const Ray ray, const Object object, float& t);

private:
    //// deprecated
    //static bool check_radius_collision(const Player player, const Object object) 
    //{
    //    float distance_from_centers = glm::distance(player.GetBoundaryBox().GetCenterPoint(), object.GetBoundaryBox().GetCenterPoint());
    //    float distance_from_edges = distance_from_centers
    //                                    - (distance(player.GetBoundaryBox().GetMinPoint(), player.GetBoundaryBox().GetMaxPoint()) / 2)
    //                                    - (distance(object.GetBoundaryBox().GetMinPoint(), object.GetBoundaryBox().GetMaxPoint()) / 2);

    //    return player.GetRadius() > distance_from_edges;
    //}
};

