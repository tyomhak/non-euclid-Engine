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
    static void calculate_min_max_points(Object object)
    {
        p_min.x = INT_MAX;
        p_min.y = INT_MAX;
        p_min.z = INT_MAX;

        p_max.x = INT_MIN;
        p_max.y = INT_MIN;
        p_max.z = INT_MIN;

        long meshes_quantity = object.model->meshes.size();
        for(int i{0}; i < meshes_quantity; ++i)
        {
            int amount = object.model->meshes[i].vertices.size();
            for (int j{ 0 }; j < amount; ++j)
            {
                // min point assigning
                if (object.model->meshes[i].vertices[j].Position.x < p_min.x) { p_min.x = object.model->meshes[i].vertices[j].Position.x; }
                if (object.model->meshes[i].vertices[j].Position.y < p_min.y) { p_min.y = object.model->meshes[i].vertices[j].Position.y; }
                if (object.model->meshes[i].vertices[j].Position.z < p_min.z) { p_min.z = object.model->meshes[i].vertices[j].Position.z; }
                // max point assigning
                if (object.model->meshes[i].vertices[j].Position.x > p_max.x) { p_max.x = object.model->meshes[i].vertices[j].Position.x; }
                if (object.model->meshes[i].vertices[j].Position.y > p_max.y) { p_max.y = object.model->meshes[i].vertices[j].Position.y; }
                if (object.model->meshes[i].vertices[j].Position.z > p_max.z) { p_max.z = object.model->meshes[i].vertices[j].Position.z; }
            }
        }
    }
    // set min and max points for aabb
    void set_aabb_p(const glm::vec3 min, const glm::vec3 max)
    {
        p_min = min;
        p_max = max;
    }
    // intersection check of aabb with point
    static bool intersect(const Camera camera, const Object object)
    {
        calculate_min_max_points(object);   // calcuate the min and max points before intersection check

        //std::cout << "[" << camera.Position.x << "," << camera.Position.y << "," << camera.Position.z << "] "
        //    << "[" << p_min.x << "," << p_min.y << "," << p_min.z << "] "
        //    << "[" << p_max.x << "," << p_max.y << "," << p_max.z << "] " << std::endl;

        return (camera.Position.x >= p_min.x && camera.Position.x <= p_max.x)
            && (camera.Position.y >= p_min.y && camera.Position.y <= p_max.y)
            && (camera.Position.z >= p_min.z && camera.Position.z <= p_max.z);
    }
    // intersection check of aabb with aabb
    static bool intersect(const Object object1, const Object object2)
    {
        //return (object1.p_min.x <= object2.p_max.x && object1.p_max.x >= object2.p_min.x)
        //    && (object1.p_min.y <= object2.p_max.y && object1.p_max.y >= object2.p_min.y)
        //    && (object1.p_min.z <= object2.p_min.z && object1.p_max.z >= object2.p_min.z);
    }

private:
    static glm::vec3 p_min;
    static glm::vec3 p_max;
};

glm::vec3 AABB::p_min = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 AABB::p_max = glm::vec3(0.0f, 0.0f, 0.0f);

#endif  //!AABB_DEF