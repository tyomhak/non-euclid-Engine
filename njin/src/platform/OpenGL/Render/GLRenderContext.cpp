#include "platform/OpenGL/Render/GLRenderContext.hpp"
#include "core.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <assert.h>

namespace njin::render::open_gl
{

GLRenderContext::GLRenderContext(GLFWwindow* window)
    : _window_handle(window)
{}

void GLRenderContext::Init()
{
    SetCurrent();
    
    auto glad_load_success = gladLoaderLoadGL();
    assert(glad_load_success);

    auto vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    auto renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    auto version = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    _info = {
        vendor,
        renderer,
        version
    };

    Logger::Log("Render Info: ");
    Logger::Log("\tVendor: {}", vendor);
    Logger::Log("\tRenderer: {}", renderer);
    Logger::Log("\tVersion: {}", version);
}


void GLRenderContext::SetCurrent()
{
    glfwMakeContextCurrent(_window_handle);
}


void GLRenderContext::SwapBuffers()
{
    glfwSwapBuffers(_window_handle);
}

void GLRenderContext::Clear()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool GLRenderContext::OnResize(WindowResizeEvent& event)
{
    glViewport(0, 0, event.GetWidth(), event.GetHeight());
    return true;
}


};