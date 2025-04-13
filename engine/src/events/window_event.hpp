#pragma once

#include "event.hpp"

namespace njin
{

class WindowResizeEvent : public Event
{
public:
    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

    WindowResizeEvent(unsigned width, unsigned height)
        : _width(width)
        , _height(height)
    {}

    std::string ToString() const 
    { 
        std::stringstream ss;
        ss << GetName() << ": " << _width << ", " << _height;
        return ss.str();
    }

    inline unsigned GetWidth() const { return _width; }
    inline unsigned GetHeight() const { return _height; }

private:
    unsigned _width, _height;
};


class WindowCloseEvent : public Event
{
public:
    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowFocusEvent : public Event
{
public:
    EVENT_CLASS_TYPE(WindowFocus)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowLostFocusEvent : public Event
{
public:
    EVENT_CLASS_TYPE(WindowLostFocus)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowMovedEvent : public Event
{
public:
    EVENT_CLASS_TYPE(WindowMoved)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

}