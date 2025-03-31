#pragma once

#include <glm/glm.hpp>

class GameObject;

class Component
{
public:
    Component(GameObject* gameObject, int priotity);
    virtual ~Component(){};

    virtual void OnStart() {}
    virtual void Update(float delta) {}

    GameObject* parent() { return _parent; }

    glm::mat4& Transform();
    glm::mat4 Transform() const;
    glm::mat4& GlobalTransform();
    glm::mat4 GlobalTransform() const;


    int priority() const { return _priority; }

private:
    GameObject* _parent;
    const int _priority{0};
};