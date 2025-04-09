#pragma once

#include "utils/id.h"
#include "core/Transform.h"

namespace render
{

class Model;

class RenderObject
{
public:
    typedef ID<Model> ID_MODEL;

    void SetModel(ID_MODEL model_id)
    {
        _model_id = model_id;
    }

    ID_MODEL GetModelID() const { return _model_id; }

    void SetWorldMat(const glm::mat4& worldMat)
    {
        _world_mat = worldMat;
    }

    glm::mat4 GetWorldMat() const 
    {
        return _world_mat;
    }

private:
    glm::mat4 _world_mat = glm::mat4(1.0f);
    ID_MODEL _model_id{ID_MODEL::uninitialized()};
};





}