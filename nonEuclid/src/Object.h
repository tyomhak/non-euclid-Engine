#pragma once

#include "Model.h"
#include "Shader.h"
#include "BoundaryBox.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object
{
protected:
    glm::mat4 worldMatrix;
    std::string ID;
    BoundaryBox boundaryBox;
    /* data */

public:
    Model* model;
    const std::string modelType;
    GLfloat yaw = -90.0f;

    Object (Model &_model, const std::string& _modelType, std::string id, glm::mat4 _worldMatrix = glm::mat4(1.0f));

    ~Object();

    std::string GetId() const
    {
        return ID;
    }

    BoundaryBox GetBoundaryBox() const 
    {
        return boundaryBox;
    }

    float GetYaw() const 
    { 
        return yaw;
    }


   void Draw(Shader &shader)
   {
        model->Draw(shader, worldMatrix);
   }

   void DrawClone(Shader &shader, glm::vec3 translate)
   {
       model->Draw(shader, glm::translate(worldMatrix, translate));
   }

    void Move(glm::vec3 translate)
    {
        worldMatrix = glm::translate(worldMatrix, translate);
        boundaryBox.Move(translate);
    }

    void SetPosition(glm::vec3 position)
    {
        glm::mat4 location(1.0f);
        worldMatrix = glm::translate(location, position);
        UpdateBoundaryBox();
    }

    void Rotate(const float angle, glm::vec3 translate)
    {
        worldMatrix = glm::rotate_slow(worldMatrix, angle, translate);
        // TODO: update min and max values of AABB in case of rotation
        
    }

    void RotateHorizontal(GLfloat degrees)
    {
        Rotate(degrees, glm::vec3(0.0f, 1.0f, 0.0f));
        yaw -= degrees;

        UpdateMinMaxPointsWorld();
    }

    void Scale(float scale_value)
    {
        glm::vec3 location = glm::vec3(worldMatrix[3][0], worldMatrix[3][1], worldMatrix[3][2]);
        boundaryBox.Move(-1.0f * location);

        boundaryBox.SetMinPoint(scale_value * boundaryBox.GetMinPoint());
        boundaryBox.SetMaxPoint(scale_value * boundaryBox.GetMaxPoint());

        boundaryBox.Move(location);

        worldMatrix = glm::scale(worldMatrix, glm::vec3(scale_value, scale_value, scale_value));
    } 

    std::vector<glm::vec3> GetVerticesWorldSpace()
    {
        std::vector<glm::vec3> all_vertices;
        for (auto& mesh : model->meshes)
        {
            for (auto& point : mesh.vertices)
            {
                all_vertices.push_back(glm::vec4(point.Position, 1.0f) * worldMatrix);
            }
        }

        return all_vertices;
    }

    std::vector<glm::vec3> GetVertices()
    {
        std::vector<glm::vec3> all_vertices;
        for (auto &mesh : model->meshes)
        {
            for (auto &point : mesh.vertices)
            {
                all_vertices.push_back(glm::vec4(point.Position, 1.0f) * worldMatrix);
            }
        }

        return all_vertices;
    }

    const glm::mat4 GetWorldMat() const { return worldMatrix; }
    void SetWorldMatrix(glm::mat4 newLocation);

private:
    void UpdateBoundaryBox();
    void UpdateMinMaxPoints();
    void UpdateMinMaxPointsWorld();

};

