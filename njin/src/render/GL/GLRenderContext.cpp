// #include "platform/OpenGL/Render/GLRenderContext.hpp"
#include "GLRenderContext.hpp"
#include "core.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <assert.h>

namespace
{

void APIENTRY gl_debug_callback(
    GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei /*length*/, const GLchar* message, const void* /*userParam*/)
{
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        return;

    const char* severity_str =
        severity == GL_DEBUG_SEVERITY_HIGH   ? "HIGH" :
        severity == GL_DEBUG_SEVERITY_MEDIUM ? "MEDIUM" :
        severity == GL_DEBUG_SEVERITY_LOW    ? "LOW" : "NOTIFICATION";

    njin::Logger::Error("GL Debug [{}] (source={} type={} id={}): {}",
                        severity_str, source, type, id, message);
}

} // anonymous namespace

namespace njin
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

    // Enable debug output in debug builds
#ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(gl_debug_callback, nullptr);
    // Suppress notification-level messages
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION,
                          0, nullptr, GL_FALSE);
    Logger::Log("GL debug output enabled");
#endif
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