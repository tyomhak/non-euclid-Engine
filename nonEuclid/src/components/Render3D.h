#pragma once

#include <glm/glm.hpp>

#include "Component.h"
#include "render/render_engine.h"
#include "utils/id.h"


class Shader;
class Model;

class Render3D : public Component
{
public:
    Render3D(GameObject* gameObject)
        : Component(gameObject, 40)
    {}

    void Update(float delta) override;
    virtual void UpdateShaderData(){}

    
    
    void SetModel(Model* model)
    { _model = model; }
    
    void SetShader(Shader* shader)
    { _shader = shader; }


    void UpdateTransformMat(const glm::mat4& objWorldMat);

private:
    ID<render::RenderObject> _rend_obj_id{};

    Shader* _shader{nullptr};
    Model* _model{nullptr};
};