#pragma once

#include "event.hpp"
#include "window_event.hpp"

namespace njin::render
{
    class RenderContext
    {
    public:
        virtual ~RenderContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
        virtual void Clear() = 0;

        bool OnEvent(Event& event){
            EventDispatcher dispatcher(event);
            return dispatcher.Dispatch<WindowResizeEvent>([this](Event& e){ 
                auto resizeEvent = static_cast<WindowResizeEvent&>(e);
                return OnResize(resizeEvent);
            });
        };

    protected:
        virtual bool OnResize(WindowResizeEvent& event){ return false; };

    };

};