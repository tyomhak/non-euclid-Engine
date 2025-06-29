#pragma once

#include "core.hpp"
#include "application.hpp"
#include "key_codes.hpp"
#include "window.hpp"
#include "input_poller.hpp"


namespace njin
{
class Input
{
public:
    static bool IsKeyPressed(KeyCode key);
    static bool IsMouseButtonPressed(MouseKeyCode mouseButton);
    static Point GetMousePosition();
};
};