#pragma once

#include "core.hpp"
#include "key_codes.hpp"
#include "application.hpp"

#include <memory>

namespace njin
{

class InputPoller
{
public:
    virtual ~InputPoller() = default;
    
    virtual bool IsKeyPressed(KeyCode key) const = 0;
    virtual bool IsMouseButtonPressed(MouseKeyCode key) const = 0;
    virtual Point GetMousePosition() const = 0;
};

};