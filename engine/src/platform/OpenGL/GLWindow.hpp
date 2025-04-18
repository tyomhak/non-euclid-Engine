#pragma once

#include "window.hpp"

class GLFWwindow;

namespace njin
{

class GLWindow : public Window
{
public:
    GLWindow(const WindowProps& props);
    ~GLWindow();

    void OnUpdate() override;

    inline int GetWidth() const override { return _window_data.width; }
    inline int GetHeight() const override { return _window_data.height;}

    void SetEventCallback(const EventCallbackFn& callback) override;
    void SetVSync(bool enabled) override;
    inline bool IsVSync() const override { return _window_data.vsync_enabled; }

private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();

private:
    struct WindowData
    {
        std::string title;
        int width;
        int height;
        bool vsync_enabled { true };

        EventCallbackFn event_callback{};
    };

    GLFWwindow* _glfw_window;
    WindowData _window_data;
};


}