#include "GLWindow.hpp"

#include <assert.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "window_event.hpp"
#include "mouse_event.hpp"
#include "key_event.hpp"

#include "GLKeyConverter.hpp"
#include "GLInput.hpp"

#include "render/render_context.hpp"
#include "Render/GLRenderContext.hpp"

namespace njin
{
    Window* Window::Create(const WindowProps& props)
    {
        return new open_gl::GLWindow(props);
    }
}


namespace njin::open_gl
{
    
static bool s_glfw_initiated = false;

GLWindow::GLWindow(const WindowProps& props)
	: Window()
	, _glfw_window(nullptr)
	, _window_data{}
{
    Init(props);
    _input.reset(new GLInputPoller(this));
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

        // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        s_glfw_initiated = success;
    }

    _window_data = WindowData {
        .title = props.title,
        .width = props.width,
        .height = props.height,
    };

    _glfw_window = glfwCreateWindow(_window_data.width, _window_data.height, _window_data.title.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(_glfw_window, &_window_data);

    _render_context = std::make_unique<njin::render::open_gl::GLRenderContext>(_glfw_window);
    _render_context->Init();

    int major = 0, minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    Logger::Log("OpenGL Info:");
    Logger::Log("\tVersion: {}.{}", major, minor);
    
    InitCallbacks();
    SetVSync(IsVSync());
}

void GLWindow::Shutdown()
{
    glfwDestroyWindow(_glfw_window);
}

void GLWindow::InitCallbacks()
{
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
            MouseKeyPressedEvent event(ToMouseKey(button));
            window_data.event_callback(event);
        }
        else if (action == GLFW_RELEASE)
        {
            MouseKeyReleasedEvent event(ToMouseKey(button));
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
        MouseScrolledEvent event((int)xoffset, (int)yoffset);
        window_data.event_callback(event);
    });

    glfwSetKeyCallback(_glfw_window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
        auto& window_data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        auto modsMask = glfwModsToKeyModifierMask(mods);

        switch (action)
        {
            case GLFW_PRESS:
            {
                auto event = KeyPressedEvent(ToKeyCode(key), 0, modsMask);
                window_data.event_callback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                auto event = KeyReleasedEvent(ToKeyCode(key), modsMask);
                window_data.event_callback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                auto event = KeyPressedEvent(ToKeyCode(key), 0, modsMask);
                window_data.event_callback(event);
                break;
            }
            default:
                break;
        }
    });
}

void GLWindow::Clear()
{
    _render_context->Clear();
}

void GLWindow::PollEvents()
{
    glfwPollEvents();
}
void GLWindow::Draw()
{
    _render_context->SwapBuffers();
}

bool GLWindow::OnEvent(Event& event)
{
    return _render_context->OnEvent(event);
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

void* GLWindow::GetNativeWindow() const
{
    return _glfw_window;
}

};