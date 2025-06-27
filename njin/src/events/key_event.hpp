#pragma once

#include "event.hpp"
#include "key_codes.hpp"

namespace njin
{

class KeyEvent : public Event
{
public:
    KeyEvent(KeyCode key_code, const KeyModifierMask& mods_mask = {})
        : _key_code(key_code)
        , _key_mods_mask(mods_mask)
    {}

    inline KeyCode GetKeyCode() const { return _key_code; }
    inline const KeyModifierMask& GetKeyModifierMask() const { return _key_mods_mask; }
    
private:
    KeyCode _key_code{KeyCode::Key_UNDEFINED};
    KeyModifierMask _key_mods_mask{};

};


class KeyPressedEvent : public KeyEvent
{
public:
    EVENT_CLASS_TYPE(KeyPressed)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

    KeyPressedEvent(KeyCode key_code, int repeat_count, const KeyModifierMask& mods_mask = {})
        : KeyEvent(key_code, mods_mask)
        , _repeat_count(repeat_count)
    {}
    
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << ": " << std::to_string(static_cast<int>(GetKeyCode())) << " (" << _repeat_count << " repeats)";
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

    using KeyEvent::KeyEvent;
};


}