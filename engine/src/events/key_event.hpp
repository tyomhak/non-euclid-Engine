#pragma once

#include "event.hpp"

namespace njin
{

class KeyEvent : public Event
{
public:
    inline int GetKeyCode() const { return _key_code; }

protected:
    KeyEvent(int key_code) 
    : _key_code(key_code)
    {}

private:
    int _key_code;
};


class KeyPressedEvent : public KeyEvent
{
public:
    EVENT_CLASS_TYPE(KeyPressed)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

    KeyPressedEvent(int key_code, int repeat_count)
        : KeyEvent(key_code)
        , _repeat_count(repeat_count)
    {}
    
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << ": " << std::to_string(GetKeyCode()) << " (" << _repeat_count << " repeats)";
        return ss.str();
    }
    
    inline int GetRepeatCount() const { return _repeat_count; }

private:
    int _repeat_count;
};


class KeyReleasedEvent : public KeyEvent
{
public:
    EVENT_CLASS_TYPE(KeyReleased)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

};


}