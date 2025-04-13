#pragma once

#include <memory>

#include "event.hpp"


namespace njin
{

class Window;

class Application
{
public:
    Application();
    ~Application();
    
    void Run();

    void OnEvent(Event& event);

    bool OnWindowClose(Event& event);

private:
    bool _is_running{true};
    std::unique_ptr<Window> _main_window{nullptr};
};


}