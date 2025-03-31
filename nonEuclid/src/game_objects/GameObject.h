#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

class Component;

class GameObject
{
public:
    virtual void OnStart();

    virtual void PreUpdate();
    virtual void Update(float delta);

    glm::mat4& Transform() { return _transform; }
    glm::mat4 Transform() const { return _transform; }

    glm::mat4& GlobalTransform() { return _global_transform; }
    glm::mat4 GlobalTransform() const { return _global_transform; }

protected:
    void UpdateGlobalTransform();

private:
    GameObject* _parent{nullptr};
    std::vector<std::unique_ptr<Component>> _components;
    glm::mat4 worldMatrix;

    glm::mat4 _transform{};
    glm::mat4 _global_transform{};
};