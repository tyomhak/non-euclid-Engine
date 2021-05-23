#pragma once
#include "Model.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Object
{
protected:
    glm::mat4 worldMatrix;
    std::string ID;
    /* data */


public:
    Model* model;
    const string modelType;
    Object (Model &_model, string _modelType, std::string id, glm::mat4 _worldMatrix = glm::mat4(1.0f));

    ~Object
   ();

    std::string getId() {
        return ID;
   }

   void Draw(Shader &shader)
   {
        model->Draw(shader, worldMatrix);
   }

   void DrawClone(Shader &shader, glm::vec3 translate)
   {
       model->Draw(shader, glm::translate(worldMatrix, translate));
   }

    void move(glm::vec3 translate)
    {
        worldMatrix = glm::translate(worldMatrix, translate);
    }

    const glm::mat4 GetWorldMat() const { return worldMatrix; }
};

Object::Object(Model &_model, string _modelType, std::string id, glm::mat4 _worldMatrix) :
modelType(_modelType),
worldMatrix(_worldMatrix),
ID(id),
model(&_model)
{
}

Object::~Object()
{
}
