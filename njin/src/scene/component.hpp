#pragma once

namespace njin
{

class Entity;

class Component
{
public:
    virtual ~Component() = default;

    virtual void on_attach(Entity& /*owner*/) {}
    virtual void on_detach() {}
    virtual void on_update(float /*dt*/) {}

    Entity* owner() const { return _owner; }

private:
    friend class Entity;
    Entity* _owner{nullptr};
};

} // namespace njin
