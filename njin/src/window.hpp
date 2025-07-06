#pragma once

#include <string>
#include <functional>
#include <memory>

#include "event.hpp"
#include "input_poller.hpp"
#include "render/render_context.hpp"

namespace njin
{
    struct WindowProps
    {
        std::string title{};
        int width{0};
        int height{0};

        WindowProps(const std::string& new_title = "NJIN Engine",
                int new_width = 1280,
                int new_height = 720)
        : title(new_title)
        , width(new_width)
        , height(new_height)
        {}
    };

    class Window
    {
        using RenderContext = render::RenderContext;

    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window();

        virtual void Clear() = 0;
        virtual void PollEvents() = 0;
        virtual void Draw() = 0;

        virtual bool OnEvent(Event& event) = 0;

        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;
        
        virtual void* GetNativeWindow() const { return nullptr; }
        InputPoller* GetInputPoller() const { return _input.get(); }
        
        static Window* Create(const WindowProps& window_props = WindowProps()); 

    protected:
        std::unique_ptr<InputPoller> _input{nullptr};
        std::unique_ptr<RenderContext> _render_context{nullptr};
    };



}