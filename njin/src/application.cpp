#include "application.hpp"

#include "window.hpp"
#include "window_event.hpp"
#include "layer.hpp"

// #include "OpenGL/Render/GLShader.hpp"
#include "render/renderer.hpp"

#include "duration.hpp"

namespace njin
{

Application::Application()
{
    _main_window = std::unique_ptr<Window>(Window::Create());
    _main_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

    const std::string default_vert_shader = R"glsl(
        #version 330 core

        layout(location = 0) in vec3 aPosition;

        void main()
        {
            gl_Position = vec4(aPosition, 1.0);
        }
    )glsl";

    const std::string default_frag_shader = R"glsl(
        #version 330 core

        uniform vec4 u_Color;

        out vec4 FragColor;

        void main()
        {
            FragColor = vec4( 0.5, 0.0, 0.5, 1.0 ); // u_Color;
        }
    )glsl";


    _default_shader.reset(Renderer::create_shader(default_vert_shader, default_frag_shader));
    if (!_default_shader) {
        // Handle shader creation failure (log error, use fallback, or throw)
        throw std::runtime_error("Failed to create default shader");
    }
    _default_shader->Bind();


    const std::vector<float> verts{
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    glCreateVertexArrays(1, &_vao);

    glCreateBuffers(1, &_vbo);
    glNamedBufferData(_vbo, sizeof(float) * verts.size(), verts.data(), GL_STATIC_DRAW);

    glVertexArrayVertexBuffer(_vao, 0, _vbo, 0, 3 * sizeof(float));

    glEnableVertexArrayAttrib(_vao, 0);
    glVertexArrayAttribFormat(_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(_vao, 0, 0);
}

Application* Application::Get()
{
    static Application app{};
    return &app;
}

Application::~Application()
{
    
}

void Application::Run()
{
    {
		// Necessary for capturing window size when the application starts.
        int width = _main_window->GetWidth();
        int height = _main_window->GetHeight();
        WindowResizeEvent onStartWindowResizeEvent(width, height);
        OnEvent(onStartWindowResizeEvent);
    }

    while (_is_running)
    {
        DurationLogger frameDuration("Time per Frame: ");
        _main_window->Clear();
        _main_window->PollEvents();

        _default_shader->Bind();
        // glUseProgram( _default_shader );
        glBindVertexArray( _vao );

        // Draw points 0-3 from the currently bound VAO with current in-use shader.
        glDrawArrays( GL_TRIANGLES, 0, 3 );

        for (auto layerPtr : _layer_stack)
            layerPtr->OnUpdate();

        _main_window->Draw();
    }
}


void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event); 
    dispatcher.Dispatch<WindowCloseEvent>([this](Event& e){ return OnWindowClose(e); });
    dispatcher.Dispatch<WindowFocusEvent>([this](Event& e){ return OnWindowFocus(e); });
    dispatcher.Dispatch<WindowLostFocusEvent>([this](Event& e){ return OnWindowLostFocus(e); });
    dispatcher.Dispatch<WindowMovedEvent>([this](Event& e){ return OnWindowMoved(e); });

    _main_window->OnEvent(event);
    for(auto it = _layer_stack.end(); it != _layer_stack.begin();)
    {
        (*--it)->OnEvent(event);
        if (event.IsHandled())
            break;
    }
}


bool Application::OnWindowClose(Event& event)
{
    _is_running = false;
    return true;
}


}