#include "GLWindow.hpp"

#include <assert.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "window_event.hpp"
#include "mouse_event.hpp"


namespace njin
{

Window* Window::Create(const WindowProps& props)
{
    return new GLWindow(props);
}



static bool s_glfw_initiated = false;

GLWindow::GLWindow(const WindowProps& props)
{
    Init(props);
}

GLWindow::~GLWindow()
{
    Shutdown();
}

void GLWindow::Init(const WindowProps& props)
{
    if (!s_glfw_initiated)
    {
        auto success = glfwInit() == GLFW_TRUE;
        assert(success);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        s_glfw_initiated = success;
    }

    _window_data = WindowData {
        .title = props.title,
        .width = props.width,
        .height = props.height,
    };

    _glfw_window = glfwCreateWindow(_window_data.width, _window_data.height, _window_data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(_glfw_window);

    auto glad_load_success = gladLoaderLoadGL();
    assert(glad_load_success);

    glfwSetWindowUserPointer(_glfw_window, &_window_data);
    SetVSync(IsVSync());


    glfwSetWindowCloseCallback(_glfw_window, [](GLFWwindow* window){
        auto& window_data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event{};
        window_data.event_callback(event);
    });

    glfwSetWindowPosCallback(_glfw_window, [](GLFWwindow* window, int x_pos, int y_pos){
        auto& window_data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        WindowMovedEvent event(x_pos, y_pos);
        window_data.event_callback(event);
    });

    glfwSetWindowSizeCallback(_glfw_window, [](GLFWwindow* window, int width, int height){
        auto& window_data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        window_data.width = width;
        window_data.height = height;

        WindowResizeEvent event(width, height);
        window_data.event_callback(event);
    });

    glfwSetWindowFocusCallback(_glfw_window, [](GLFWwindow* window, int focused){
        auto& window_data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (focused == GLFW_TRUE)
        {
            WindowFocusEvent event{};
            window_data.event_callback(event);
        }
        else
        {
            WindowLostFocusEvent event{};
            window_data.event_callback(event);
        }
    });


    glfwSetMouseButtonCallback(_glfw_window, [](GLFWwindow* window, int button, int action, int mods){
        auto& window_data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS)
        {
            MouseKeyPressedEvent event(button);
            window_data.event_callback(event);
        }
        else if (action == GLFW_RELEASE)
        {
            MouseKeyReleasedEvent event(button);
            window_data.event_callback(event);
        }
    });

    glfwSetCursorPosCallback(_glfw_window, [](GLFWwindow* window, double xpos, double ypos){
        auto& window_data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        MouseMovedEvent event((int)xpos, (int)ypos);
        window_data.event_callback(event);
    });

    glfwSetScrollCallback(_glfw_window, [](GLFWwindow* window, double xoffset, double yoffset){
        auto& window_data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        MouseScrolledEvent event((int)yoffset);
        window_data.event_callback(event);
    });
}

void GLWindow::Shutdown()
{
    glfwDestroyWindow(_glfw_window);
}


void GLWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(_glfw_window);
}

void GLWindow::SetEventCallback(const EventCallbackFn& callback)
{
    _window_data.event_callback = callback;
}

void GLWindow::SetVSync(bool enabled)
{
    glfwSwapInterval( enabled ? 1 : 0);
    _window_data.vsync_enabled = enabled;
}




    
}