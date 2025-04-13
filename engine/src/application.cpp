#include "application.hpp"

#include "window.hpp"


#include <glad/gl.h>
// #include <GLFW/glfw3.h>
// #include <glfw/glfw3.h>



#include "window_event.hpp"
#include "layer.hpp"


namespace njin
{

Application::Application()
{
    _main_window = std::unique_ptr<Window>(Window::Create());
    _main_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
}

Application::~Application()
{
    
}

void Application::Run()
{
    while (_is_running)
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);   
        _main_window->OnUpdate();

        for (auto layerPtr : _layer_stack)
            layerPtr->OnUpdate();
    }
}


void Application::OnEvent(Event& event)
{
    std::cout << event << std::endl;
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>([this](Event& e){ return OnWindowClose(e); });

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