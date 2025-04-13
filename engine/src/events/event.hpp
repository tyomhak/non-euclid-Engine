#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <sstream>

namespace njin
{

constexpr unsigned long long bit(int n) { return 1 << n; }

#define BIT(x) 1 << x

enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    KeyPressed, KeyReleased,
    MouseKeyPressed, MouseKeyReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication = bit(0),
    EventCategoryInput       = bit(1),    
    EventCategoryKeyboard    = bit(2),
    EventCategoryMouse       = bit(3),
    EventCategoryMouseButton = bit(4)
};


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                               EventType GetType() const override { return GetStaticType(); }\
                               const char* GetName() const override { return #type; } 

#define EVENT_CLASS_CATEGORY(category) int GetCategories() const override { return category; }

class EventDispatcher;

class Event
{
    friend EventDispatcher;

public:
    virtual ~Event() = default;

    virtual const char* GetName() const = 0;
    virtual EventType GetType() const = 0; 
    virtual int GetCategories() const = 0;

    virtual std::string ToString() const { return GetName(); }

    inline bool IsInCategory(EventCategory category) { return GetCategories() & category; }

private:
    bool _handled{false};
};


template<typename T>
concept event_type = requires(T e)
{
    {e.GetType()}       -> std::same_as<EventType>;
    {e.GetStaticType()} -> std::same_as<EventType>;
    {e.GetCategories()} -> std::convertible_to<int>;
};

class EventDispatcher
{
    template<event_type T>
    using EventFn = std::function<bool(T&)>;
public:
    EventDispatcher(Event& event)
        : _event(event)
    {}

    template<event_type T>
    bool Dispatch(EventFn<T> func)
    {
        if (_event.GetType() == T::GetStaticType())
        {
            _event._handled = func(*(T*)&_event);
            return true;
        }
        return false;
    }

private:
    Event& _event;
};


inline std::ostream& operator<<(std::ostream& os, Event& event)
{
    return os << event.ToString();
}


}