#pragma once

#include "key_codes.hpp"

#include <GLFW/glfw3.h>

namespace njin::open_gl
{
    KeyCode ToKeyCode(int glKey);
    MouseKeyCode ToMouseKey(int glKey);

    uint8_t glfwToKeyModifierMask(int glfwMods);
    KeyModifierMask glfwModsToKeyModifierMask(int glfwMods);


    int ToGLFWKeyCode(KeyCode key);
    int ToGLFWMouseKey(MouseKeyCode mouseKey);
};
