#pragma once

#include "layer.hpp"
#include "window.hpp"

#include "mouse_event.hpp"
#include "key_event.hpp"
#include "window_event.hpp"

namespace njin
{

class UILayer : public Layer
{
public:
    UILayer(Window* window);
    ~UILayer();

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate() override;
    void OnEvent(Event& e) override;

protected:
    void Init(Window* window);

    bool OnMouseMovedEvent(MouseMovedEvent&);
    bool OnMouseKeyPressedEvent(MouseKeyPressedEvent&);
    bool OnMouseKeyReleasedEvent(MouseKeyReleasedEvent&);
    bool OnMouseScrolledEvent(MouseScrolledEvent&);
    bool OnWindowFocusEvent(WindowFocusEvent&);
    bool OnWindowLostFocusEvent(WindowLostFocusEvent&);
    bool OnWindowMovedEvent(WindowMovedEvent&);
    bool OnWindowResizeEvent(WindowResizeEvent&);
    bool OnKeyPressedEvent(KeyPressedEvent&);
    bool OnKeyReleasedEvent(KeyReleasedEvent&);
    
    
private:
    Window* _parent_window{nullptr};
    void* _context{nullptr};
};


}