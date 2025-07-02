#include "platform/OpenGL/Render/GLRenderContext.hpp"

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
    glfwMakeContextCurrent(_window_handle);
    auto glad_load_success = gladLoaderLoadGL();
    assert(glad_load_success);
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