#pragma once

#include "Model.h"
#include "Shader.h"
#include "BoundaryBox.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object
{
public:
    Object (Model &_model, string _modelType, std::string id, glm::mat4 _worldMatrix = glm::mat4(1.0f));
    ~Object();

    std::string GetId() const { return ID; }

    BoundaryBox GetBoundaryBox() const { return boundaryBox; }
    float GetYaw() const { return yaw; }

    void Draw(Shader& shader);
    void DrawClone(Shader& shader, glm::vec3 translate);

    void SetPosition(glm::vec3 position);
    virtual void Move(glm::vec3 translate);
    void Rotate(const float angle, glm::vec3 translate);
    void RotateHorizontal(GLfloat degrees);

    void Scale(float scale_value);

    vector<glm::vec3> GetVerticesWorldSpace();
    vector<glm::vec3> GetVertices();

    virtual const glm::mat4 GetWorldMat() const; 
    void SetWorldMatrix(glm::mat4 newLocation);

private:
    void UpdateBoundaryBox();
    void UpdateMinMaxPoints();
    void UpdateMinMaxPointsWorld();

public:
    Model* model;
    const string modelType;
    GLfloat yaw = -90.0f;

protected:
    glm::mat4 worldMatrix;
    std::string ID;
    BoundaryBox boundaryBox;
};

