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

void GameObject::PreUpdate()
{
    
}

void GameObject::Update(float delta)
{
    for (auto& component : _components)
        component->Update(delta);
}

void GameObject::UpdateGlobalTransform()
{
    if (_parent)
        _global_transform = _parent->GlobalTransform() * _global_transform;
    else
        _global_transform = _transform;
}