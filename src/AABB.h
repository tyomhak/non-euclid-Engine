#ifndef AABB_DEF
#define AABB_DEF

#include "IncludeHeaders.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Object.h"


class AABB {
public:
    AABB() {};

    // set min and max points for aabb
    void set_aabb_p(const glm::vec3 min, const glm::vec3 max)
    {
        p_min = min;
        p_max = max;
    }
    // intersection check of aabb with point
    static bool intersect(const Camera camera, const Object object)
    {
        //calculate_min_max_points(object);   // calcuate the min and max points before intersection check

        //std::cout << "[" << camera.Position.x << "," << camera.Position.y << "," << camera.Position.z << "] "
        //    << "[" << p_min.x << "," << p_min.y << "," << p_min.z << "] "
        //    << "[" << p_max.x << "," << p_max.y << "," << p_max.z << "] " << std::endl;

        return (camera.Position.x >= object.get_min_p().x && camera.Position.x <= object.get_max_p().x)
            && (camera.Position.y >= object.get_min_p().y && camera.Position.y <= object.get_max_p().y)
            && (camera.Position.z >= object.get_min_p().z && camera.Position.z <= object.get_max_p().z);
    }
    // intersection check of aabb with aabb
    static bool intersect(const Object object1, const Object object2)
    {
        return (object1.get_min_p().x <= object2.get_max_p().x && object1.get_max_p().x >= object2.get_min_p().x)
            && (object1.get_min_p().y <= object2.get_max_p().y && object1.get_max_p().y >= object2.get_min_p().y)
            && (object1.get_min_p().z <= object2.get_max_p().z && object1.get_max_p().z >= object2.get_min_p().z);
    }

private:
    static glm::vec3 p_min;
    static glm::vec3 p_max;
};

glm::vec3 AABB::p_min = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 AABB::p_max = glm::vec3(0.0f, 0.0f, 0.0f);

#endif  //!AABB_DEF