#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "core/Transform.h"

class Component;

class GameObject
{
public:
    virtual void OnStart();
    virtual void Update(float delta);

    glm::mat4 GetTransformMat() const { return _local_transform.get_transform_mat(); }
    glm::mat4 GetGlobalTransformMat() const { return _parent_global_transform * GetTransformMat(); }

    void Translate(const glm::vec3& vec);
    void SetPosition(const glm::vec3& pos);
    void Rotate(float degree, const glm::vec3& axis);
    void SetScale(const glm::vec3& v_scale);

    template<typename Comp, typename... ArgTypes>
    void AddComponent(ArgTypes... args)
    {
        _components.push_back(new Comp(this, args...));
    }

protected:
    void SetParentGlobalTransformMat(const glm::mat4& mat);

private:
    void PropogateTransformChanged();

private:
    GameObject* _parent{nullptr};
    std::vector<GameObject> _children{};
    std::vector<std::unique_ptr<Component>> _components;
    Transform _local_transform{};
    glm::mat4 _parent_global_transform = glm::mat4(1.0f);
};