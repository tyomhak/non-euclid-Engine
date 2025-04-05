#include "GameObject.h"

#include <algorithm>
#include <functional>

#include "Component.h"

void GameObject::OnStart()
{
    auto priotity_sorting = [](const auto& lComponent, const auto& rComponent){ 
        return lComponent->priority() < rComponent->priority();
    };
    std::sort(_components.begin(), _components.end(), priotity_sorting);

    for (auto& component : _components)
        component->OnStart();
}

void GameObject::Update(float delta)
{
    for (auto& component : _components)
        component->Update(delta);
}

void GameObject::Translate(const glm::vec3& vec)
{
    _local_transform.translate(vec);
}
void GameObject::SetPosition(const glm::vec3& pos)
{
    _local_transform.set_position(pos);
}
void GameObject::Rotate(float degree, const glm::vec3& axis)
{
    _local_transform.rotate(degree, axis);
}
void GameObject::SetScale(const glm::vec3& v_scale)
{
    _local_transform.set_scale(v_scale);
}

void GameObject::SetParentGlobalTransformMat(const glm::mat4& mat)
{
    _parent_global_transform = mat;
    PropogateTransformChanged();
}
void GameObject::PropogateTransformChanged()
{
    for (auto& child : _children)
    {
        child.SetParentGlobalTransformMat(GetGlobalTransformMat());
    }
}