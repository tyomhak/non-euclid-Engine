#pragma once

#include "key_codes.hpp"
#include "input_poller.hpp"

namespace njin::open_gl {
    
class GLWindow;

class GLInputPoller : public InputPoller
{
public:
    GLInputPoller(GLWindow* window);

    bool IsKeyPressed(KeyCode key) const override;
    bool IsMouseButtonPressed(MouseKeyCode key) const override;
    Point GetMousePosition() const override;

private:
    GLWindow* _windowPtr{nullptr};
};


};