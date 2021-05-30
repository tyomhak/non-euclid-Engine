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
    const string modelType;
    Object (Model &_model, string _modelType, std::string id, glm::mat4 _worldMatrix = glm::mat4(1.0f));

    ~Object();

    std::string getId()
    {
        return ID;
    }

    BoundaryBox getBoundaryBox() const 
    {
        return boundaryBox;
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

    void setPosition(glm::vec3 position)
    {
        glm::mat4 location(1.0f);
        worldMatrix = glm::translate(location, position);
        updateBoundaryBox();
    }

    void rotate(const float angle, glm::vec3 translate)
    {
        worldMatrix = glm::rotate_slow(worldMatrix, angle, translate);
        // TODO: update min and max values of AABB in case of rotation
    }

    vector<glm::vec3> get_vertices_in_world_space()
    {
        vector<glm::vec3> all_vertices;
        for (auto& mesh : model->meshes)
        {
            for (auto& point : mesh.vertices)
            {
                all_vertices.push_back(glm::vec4(point.Position, 1.0f) * worldMatrix);
            }
        }

        return all_vertices;
    }

    void SetWorldMatrix(glm::mat4 newLocation) { worldMatrix = newLocation; };

    vector<glm::vec3> GetVertices()
    {
        vector<glm::vec3> all_vertices;
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

private:

    void updateBoundaryBox()
    {
        updateMinMaxPoints();
        boundaryBox.Move(glm::vec3(worldMatrix[3][0], worldMatrix[3][1], worldMatrix[3][2]));
    }

    void updateMinMaxPoints() {
        float minX = FLT_MAX;
        float minY = FLT_MAX;
        float minZ = FLT_MAX;

        float maxX = FLT_MIN;
        float maxY = FLT_MIN;
        float maxZ = FLT_MIN;

        long meshes_quantity = (long)this->model->meshes.size();
        for (int i{ 0 }; i < meshes_quantity; ++i)
        {
            int amount = (int)this->model->meshes[i].vertices.size();
            for (int j{ 0 }; j < amount; ++j)
            {
                // min point assigning
                if (this->model->meshes[i].vertices[j].Position.x < minX) { minX = this->model->meshes[i].vertices[j].Position.x; }
                if (this->model->meshes[i].vertices[j].Position.y < minY) { minY = this->model->meshes[i].vertices[j].Position.y; }
                if (this->model->meshes[i].vertices[j].Position.z < minZ) { minZ = this->model->meshes[i].vertices[j].Position.z; }
                
                // max point assigning
                if (this->model->meshes[i].vertices[j].Position.x > maxX) { maxX = this->model->meshes[i].vertices[j].Position.x; }
                if (this->model->meshes[i].vertices[j].Position.y > maxY) { maxY = this->model->meshes[i].vertices[j].Position.y; }
                if (this->model->meshes[i].vertices[j].Position.z > maxZ) { maxZ = this->model->meshes[i].vertices[j].Position.z; }
                
            }
        }
        // update min and max of AABB
        boundaryBox.setMinPoint(glm::vec3(minX, minY, minZ));
        boundaryBox.setMaxPoint(glm::vec3(maxX, maxY, maxZ));
    }

};

Object::Object(Model &_model, string _modelType, std::string id, glm::mat4 _worldMatrix) :
modelType(_modelType),
worldMatrix(_worldMatrix),
ID(id),
model(&_model)
{
    updateBoundaryBox();
}

Object::~Object()
{ }
