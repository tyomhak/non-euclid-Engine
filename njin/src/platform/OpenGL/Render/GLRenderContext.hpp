#pragma once

#include "render/render_context.hpp"

class GLFWwindow;

namespace njin::render::open_gl
{

    class GLRenderContext : public RenderContext
    {
    public:
        GLRenderContext(GLFWwindow* window);

        void Init() override;
        void SwapBuffers() override;
        void Clear() override;

        bool OnResize(WindowResizeEvent& event) override;
    
    
    private:
        GLFWwindow* _window_handle{nullptr};
    };




}