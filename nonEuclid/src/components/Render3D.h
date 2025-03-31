#pragma once

#include "Component.h"

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

private:
    Shader* _shader{nullptr};
    Model* _model{nullptr};
};