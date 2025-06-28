#include "application.hpp"

#include "window.hpp"
#include "window_event.hpp"
#include "layer.hpp"


namespace njin
{

Application::Application()
{
    _main_window = std::unique_ptr<Window>(Window::Create());
    _main_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
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
        _main_window->Clear();
        _main_window->PollEvents();

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