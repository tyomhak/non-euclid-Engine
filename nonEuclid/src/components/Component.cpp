#include "Component.h"

#include "GameObject.h"

Component::Component(GameObject* gameObject, int priority)
    : _parent(gameObject)
    , _priority(priority)
{}

glm::mat4& Component::Transform() {
    return _parent->Transform();
}
glm::mat4 Component::Transform() const {
    return _parent->Transform();
}
glm::mat4& Component::GlobalTransform() {
    return _parent->GlobalTransform();
}
glm::mat4 Component::GlobalTransform() const {
    return _parent->GlobalTransform();
}