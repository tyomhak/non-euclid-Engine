#pragma once

#include <string>
#include <functional>

#include "event.hpp"

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
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        static Window* Create(const WindowProps& window_props = WindowProps());
    };



}