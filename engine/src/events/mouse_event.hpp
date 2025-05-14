#pragma once

#include "event.hpp"

namespace njin
{

class MouseKeyEvent : public Event
{
public:
    inline int GetKeyCode() const { return _key_code; }

protected:
    MouseKeyEvent(int key_code) 
        : _key_code(key_code)
    {}

    std::string ToString() const 
    { 
        std::stringstream ss;
        ss << GetName() << ": button_" << _key_code;
        return ss.str();
    }

private:
    int _key_code;
};

class MouseKeyPressedEvent : public MouseKeyEvent
{
public:
    EVENT_CLASS_TYPE(MouseKeyPressed)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

    MouseKeyPressedEvent(int key_code)
        : MouseKeyEvent(key_code)
    {}
};

class MouseKeyReleasedEvent : public MouseKeyEvent
{
public:
    EVENT_CLASS_TYPE(MouseKeyReleased)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

    MouseKeyReleasedEvent(int key_code)
        : MouseKeyEvent(key_code)
    {}
};

class MouseMovedEvent : public Event
{
public:
    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

    MouseMovedEvent(int x_position, int y_position)
        : _x_position(x_position)
        , _y_position(y_position)
    {}

    int GetXPosition() const { return _x_position; }
    int GetYPosition() const { return _y_position; }

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << GetName() << ": " << _x_position << ", " << _y_position;
        return ss.str();
    }

private:
    int _x_position, _y_position;
};

class MouseScrolledEvent : public Event
{
public:
    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

    MouseScrolledEvent(int x_scroll, int y_scroll)
        : _x_scroll(x_scroll), _y_scroll(y_scroll)
    {}

    inline int GetXScroll() const { return _x_scroll; }
    inline int GetYScroll() const { return _y_scroll; }

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << GetName() << "-- x:" << _x_scroll << ", y:" << _y_scroll;
        return ss.str();
    }

private:
    int _x_scroll, _y_scroll;
};
    



}