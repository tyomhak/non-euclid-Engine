#pragma once

#include <memory>

#include "event.hpp"
#include "layer_stack.hpp"

namespace njin
{

class Window;

class Application
{
public:
    Application();
    virtual ~Application();
    
    void Run();

    void OnEvent(Event& event);
    virtual bool OnWindowClose(Event& event);
    virtual bool OnWindowFocus(Event& event) { return true; }
    virtual bool OnWindowLostFocus(Event& event) { return true; }
    virtual bool OnWindowMoved(Event& event) { return true; }

    void AttachLayer(Layer* layer) { _layer_stack.PushLayer(layer); }
    void DetachLayer(Layer* layer) { _layer_stack.PopLayer(layer); }

    void AttachOverlay(Layer* overlay) { _layer_stack.PushOverlay(overlay); }
    void DetachOverlay(Layer* overlay) { _layer_stack.PopOverlay(overlay); }
    
private:
    bool _is_running{true};
    std::unique_ptr<Window> _main_window{nullptr};
    LayerStack _layer_stack{};
};


}