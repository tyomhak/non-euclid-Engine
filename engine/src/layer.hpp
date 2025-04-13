#pragma once

#include "event.hpp"

namespace njin
{

class Layer
{
public:
    Layer(const std::string& name)
        : _name(name)
    {}

    virtual ~Layer(){}

    virtual void OnUpdate(){}
    virtual void OnEvent(Event& e){}

    virtual void OnAttach(){}
    virtual void OnDetach(){}

    inline const std::string& GetName() const { return _name; }

protected:
    std::string _name{};

};


}