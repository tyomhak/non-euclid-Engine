#pragma once

#include "transform.hpp"
#include "component.hpp"

#include <memory>
#include <vector>
#include <string>
#include <algorithm>

namespace njin
{

class Entity
{
public:
    explicit Entity(std::string name = "Entity")
        : _name(std::move(name))
    {}

    ~Entity()
    {
        for (auto& comp : _components)
            comp->on_detach();
    }

    // Non-copyable, movable.
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity(Entity&&) noexcept = default;
    Entity& operator=(Entity&&) noexcept = default;

    // --- Components ---

    template<typename T, typename... Args>
    T& add_component(Args&&... args)
    {
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->_owner = this;
        T& ref = *comp;
        _components.push_back(std::move(comp));
        ref.on_attach(*this);
        return ref;
    }

    template<typename T>
    T* get_component() const
    {
        for (auto& comp : _components)
        {
            T* cast = dynamic_cast<T*>(comp.get());
            if (cast)
                return cast;
        }
        return nullptr;
    }

    template<typename T>
    bool has_component() const
    {
        return get_component<T>() != nullptr;
    }

    // --- Lifecycle ---

    void update(float dt)
    {
        for (auto& comp : _components)
            comp->on_update(dt);
    }

    // --- Public data ---

    Transform transform{};

    const std::string& name() const { return _name; }

    bool is_active() const { return _active; }
    void set_active(bool active) { _active = active; }

private:
    std::string _name;
    bool _active{true};
    std::vector<std::unique_ptr<Component>> _components;
};

} // namespace njin
