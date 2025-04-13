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

    MouseScrolledEvent(int scrolled_by)
        : _scrolled_by(scrolled_by)
    {}

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << GetName() << ": " << _scrolled_by;
        return ss.str();
    }

private:
    int _scrolled_by;
};
    



}