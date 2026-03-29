#pragma once

#include <memory>

#include "event.hpp"
#include "layer_stack.hpp"

#include "render/renderer.hpp"

#include <glm/glm.hpp>

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

    // Renderer
    std::unique_ptr<rend::Renderer> _renderer{nullptr};

    // Demo scene resources (temporary — replaced by Scene in Phase 2)
    rend::ShaderID _demo_shader{};
    rend::BufferID _demo_vbo{};
    rend::BufferID _demo_ibo{};
    rend::PipelineID _demo_pipeline{};
    rend::TextureID _demo_texture{};

    // Demo camera (temporary — replaced by Camera component in Phase 2)
    glm::vec3 _camera_pos{0.0f, 0.0f, 3.0f};
    float _camera_yaw{-90.0f};
    float _camera_pitch{0.0f};
};


}