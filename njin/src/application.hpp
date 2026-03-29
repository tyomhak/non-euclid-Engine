#pragma once

#include <memory>
#include <chrono>

#include "event.hpp"
#include "layer_stack.hpp"

#include "render/renderer.hpp"
#include "scene/scene.hpp"

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

    rend::Renderer& GetRenderer() { return *_renderer; }
    Scene& GetScene() { return _scene; }

private:
    bool OnWindowClose(Event& event);
    bool OnWindowFocus(Event& event) { return true; }
    bool OnWindowLostFocus(Event& event) { return true; }
    bool OnWindowMoved(Event& event) { return true; }

    void BuildDemoScene();
    
protected:
    bool _is_running{true};
    std::unique_ptr<Window> _main_window{nullptr};
    LayerStack _layer_stack{};

    // Renderer & Scene
    std::unique_ptr<rend::Renderer> _renderer{nullptr};
    Scene _scene{};

    // Fixed timestep
    static constexpr float FIXED_DT = 1.0f / 60.0f;
    float _accumulator{0.0f};
    std::chrono::steady_clock::time_point _last_frame_time{};
};


}