#include "Object.h"


Object::Object(Model& _model, string _modelType, std::string id, glm::mat4 _worldMatrix) :
    modelType(_modelType),
    worldMatrix(_worldMatrix),
    ID(id),
    model(&_model)
{
    UpdateBoundaryBox();
}

Object::~Object()
{ }


void Object::Draw(Shader& shader)
{
    model->Draw(shader, worldMatrix);
}

void Object::DrawClone(Shader& shader, glm::vec3 translate)
{
    model->Draw(shader, glm::translate(worldMatrix, translate));
}

void Object::SetPosition(glm::vec3 position)
{
    glm::mat4 location(1.0f);
    worldMatrix = glm::translate(location, position);
    UpdateBoundaryBox();
}

void Object::Move(glm::vec3 translate)
{
    worldMatrix = glm::translate(worldMatrix, translate);
    boundaryBox.Move(translate);
}

void Object::Rotate(const float angle, glm::vec3 translate)
{
    worldMatrix = glm::rotate_slow(worldMatrix, angle, translate);
    // TODO: update min and max values of AABB in case of rotation

}

void Object::RotateHorizontal(GLfloat degrees)
{
    Rotate(degrees, glm::vec3(0.0f, 1.0f, 0.0f));
    yaw -= degrees;

    UpdateMinMaxPointsWorld();
}


void Object::Scale(float scale_value)
{
    glm::vec3 location = glm::vec3(worldMatrix[3][0], worldMatrix[3][1], worldMatrix[3][2]);
    boundaryBox.Move(-1.0f * location);

    boundaryBox.SetMinPoint(scale_value * boundaryBox.GetMinPoint());
    boundaryBox.SetMaxPoint(scale_value * boundaryBox.GetMaxPoint());

    boundaryBox.Move(location);

    worldMatrix = glm::scale(worldMatrix, glm::vec3(scale_value, scale_value, scale_value));
}

vector<glm::vec3> Object::GetVerticesWorldSpace()
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

vector<glm::vec3> Object::GetVertices()
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

const glm::mat4 Object::GetWorldMat() const { return worldMatrix; }

void Object::SetWorldMatrix(glm::mat4 newLocation)
{
    worldMatrix = newLocation;
    UpdateBoundaryBox();
}


void Object::UpdateBoundaryBox()
{
    UpdateMinMaxPoints();
    boundaryBox.Move(glm::vec3(worldMatrix[3][0], worldMatrix[3][1], worldMatrix[3][2]));
}

void Object::UpdateMinMaxPoints() 
{
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
    boundaryBox.SetMinPoint(glm::vec3(minX, minY, minZ));
    boundaryBox.SetMaxPoint(glm::vec3(maxX, maxY, maxZ));
}

void Object::UpdateMinMaxPointsWorld() 
{
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
            glm::vec3 Position = this->model->meshes[i].vertices[j].Position;
            Position = worldMatrix * glm::vec4(Position, 1.0f);

            // min point assigning
            if (Position.x < minX) { minX = Position.x; }
            if (Position.y < minY) { minY = Position.y; }
            if (Position.z < minZ) { minZ = Position.z; }

            // max point assigning
            if (Position.x > maxX) { maxX = Position.x; }
            if (Position.y > maxY) { maxY = Position.y; }
            if (Position.z > maxZ) { maxZ = Position.z; }

        }
    }
    // update min and max of AABB
    boundaryBox.SetMinPoint(glm::vec3(minX, minY, minZ));
    boundaryBox.SetMaxPoint(glm::vec3(maxX, maxY, maxZ));
}