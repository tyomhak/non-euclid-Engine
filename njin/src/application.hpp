#pragma once

#include <memory>

#include "event.hpp"
#include "layer_stack.hpp"

namespace njin
{

class Window;

class Application
{
protected:
    Application();

public:
    static Application* Get();
    ~Application();
    
    void Run();

    void OnEvent(Event& event);

    void AttachLayer(Layer* layer) { _layer_stack.PushLayer(layer); }
    void DetachLayer(Layer* layer) { _layer_stack.PopLayer(layer); }

    void AttachOverlay(Layer* overlay) { _layer_stack.PushOverlay(overlay); }
    void DetachOverlay(Layer* overlay) { _layer_stack.PopOverlay(overlay); }

    inline Window* GetMainWindow() const { return _main_window.get(); }

private:
    bool OnWindowClose(Event& event);
    bool OnWindowFocus(Event& event) { return true; }
    bool OnWindowLostFocus(Event& event) { return true; }
    bool OnWindowMoved(Event& event) { return true; }
    
protected:
    bool _is_running{true};
    std::unique_ptr<Window> _main_window{nullptr};
    LayerStack _layer_stack{};
};


}