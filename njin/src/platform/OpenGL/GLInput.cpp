#include "GLInput.hpp"

#include "GLKeyConverter.hpp"
#include "GLWindow.hpp"

#include <GLFW/glfw3.h>

#include <cassert>


namespace njin::open_gl 
{


GLInputPoller::GLInputPoller(GLWindow* window)
{
    assert(window != nullptr && "GLInputPoller: window pointer must not be null");
    _windowPtr = window;
}


bool GLInputPoller::IsKeyPressed(KeyCode key) const
{
    return GLFW_PRESS == glfwGetKey(static_cast<GLFWwindow*>(_windowPtr->GetNativeWindow()), ToGLFWKeyCode(key));
}
bool GLInputPoller::IsMouseButtonPressed(MouseKeyCode mouseKey) const
{
    return GLFW_PRESS == glfwGetMouseButton(static_cast<GLFWwindow*>(_windowPtr->GetNativeWindow()), ToGLFWMouseKey(mouseKey));
}
Point GLInputPoller::GetMousePosition() const
{
    double xpos, ypos;
    glfwGetCursorPos(static_cast<GLFWwindow*>(_windowPtr->GetNativeWindow()), &xpos, &ypos);
    return Point{ static_cast<int>(xpos), static_cast<int>(ypos) };
}

} // namespace njin::open_gl
