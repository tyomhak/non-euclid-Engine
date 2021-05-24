#pragma once
#include "Model.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object
{
    

private:
    glm::vec3 obj_min_p;
    glm::vec3 obj_max_p;

protected:
    glm::mat4 worldMatrix;
    std::string ID;
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

    const glm::vec3 get_min_p() const
    {
        return obj_min_p;
    }
    const glm::vec3 get_max_p() const
    {
        return obj_max_p;
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
    }

    vector<glm::vec3> ReturnVertices()
    {
        vector<glm::vec3> all_vertices;
        for (auto &mesh : model->meshes)
        {
            for (auto &point : mesh.vertices)
            {
                all_vertices.push_back(point.Position);
            }
        }

        return all_vertices;
    }

    void calculate_min_max_points() {
        obj_min_p.x = INT_MAX;
        obj_min_p.y = INT_MAX;
        obj_min_p.z = INT_MAX;

        obj_max_p.x = INT_MIN;
        obj_max_p.y = INT_MIN;
        obj_max_p.z = INT_MIN;

        long meshes_quantity = (long)this->model->meshes.size();
        for (int i{ 0 }; i < meshes_quantity; ++i)
        {
            int amount = (int)this->model->meshes[i].vertices.size();
            for (int j{ 0 }; j < amount; ++j)
            {
                // min point assigning
                if (this->model->meshes[i].vertices[j].Position.x < obj_min_p.x) { obj_min_p.x = this->model->meshes[i].vertices[j].Position.x; }
                if (this->model->meshes[i].vertices[j].Position.y < obj_min_p.y) { obj_min_p.y = this->model->meshes[i].vertices[j].Position.y; }
                if (this->model->meshes[i].vertices[j].Position.z < obj_min_p.z) { obj_min_p.z = this->model->meshes[i].vertices[j].Position.z; }
                // max point assigning
                if (this->model->meshes[i].vertices[j].Position.x > obj_max_p.x) { obj_max_p.x = this->model->meshes[i].vertices[j].Position.x; }
                if (this->model->meshes[i].vertices[j].Position.y > obj_max_p.y) { obj_max_p.y = this->model->meshes[i].vertices[j].Position.y; }
                if (this->model->meshes[i].vertices[j].Position.z > obj_max_p.z) { obj_max_p.z = this->model->meshes[i].vertices[j].Position.z; }
            }
        }
    }

    const glm::mat4 GetWorldMat() const { return worldMatrix; }
};

Object::Object(Model &_model, string _modelType, std::string id, glm::mat4 _worldMatrix) :
modelType(_modelType),
worldMatrix(_worldMatrix),
ID(id),
model(&_model)
{
    calculate_min_max_points();
}

Object::~Object()
{ }
