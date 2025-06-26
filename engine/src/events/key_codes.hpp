#pragma once
#include <cstdint>

namespace njin
{

enum class KeyCode : int
{
    Key_UNDEFINED = 0,

    Key_SPACE,             
    Key_APOSTROPHE,        
    Key_COMMA,             
    Key_MINUS,             
    Key_PERIOD,            
    Key_SLASH,             
    Key_0,                 
    Key_1,                 
    Key_2,                 
    Key_3,                 
    Key_4,                 
    Key_5,                 
    Key_6,                 
    Key_7,                 
    Key_8,                 
    Key_9,                 
    Key_SEMICOLON,         
    Key_EQUAL,             
    Key_A,                 
    Key_B,                 
    Key_C,                 
    Key_D,                 
    Key_E,                 
    Key_F,                 
    Key_G,                 
    Key_H,                 
    Key_I,                 
    Key_J,                 
    Key_K,                 
    Key_L,                 
    Key_M,                 
    Key_N,                 
    Key_O,                 
    Key_P,                 
    Key_Q,                 
    Key_R,                 
    Key_S,                 
    Key_T,                 
    Key_U,                 
    Key_V,                 
    Key_W,                 
    Key_X,                 
    Key_Y,                 
    Key_Z,                 
    Key_LEFT_BRACKET,      
    Key_BACKSLASH,         
    Key_RIGHT_BRACKET,     
    Key_GRAVE_ACCENT,      
    Key_WORLD_1,           
    Key_WORLD_2,           
    Key_ESCAPE,            
    Key_ENTER,             
    Key_TAB,               
    Key_BACKSPACE,         
    Key_INSERT,            
    Key_DELETE,            
    Key_RIGHT,             
    Key_LEFT,              
    Key_DOWN,              
    Key_UP,                
    Key_PAGE_UP,           
    Key_PAGE_DOWN,         
    Key_HOME,              
    Key_END,               
    Key_CAPS_LOCK,         
    Key_SCROLL_LOCK,       
    Key_NUM_LOCK,          
    Key_PRINT_SCREEN,      
    Key_PAUSE,             
    Key_F1,                
    Key_F2,                
    Key_F3,                
    Key_F4,                
    Key_F5,                
    Key_F6,                
    Key_F7,                
    Key_F8,                
    Key_F9,                
    Key_F10,               
    Key_F11,               
    Key_F12,               
    Key_F13,               
    Key_F14,               
    Key_F15,               
    Key_F16,               
    Key_F17,               
    Key_F18,               
    Key_F19,               
    Key_F20,               
    Key_F21,               
    Key_F22,               
    Key_F23,               
    Key_F24,               
    Key_F25,               
    Key_KP_0,              
    Key_KP_1,              
    Key_KP_2,              
    Key_KP_3,              
    Key_KP_4,              
    Key_KP_5,              
    Key_KP_6,              
    Key_KP_7,              
    Key_KP_8,              
    Key_KP_9,              
    Key_KP_DECIMAL,        
    Key_KP_DIVIDE,         
    Key_KP_MULTIPLY,       
    Key_KP_SUBTRACT,       
    Key_KP_ADD,            
    Key_KP_ENTER,          
    Key_KP_EQUAL,          
    Key_LEFT_SHIFT,        
    Key_LEFT_CONTROL,      
    Key_LEFT_ALT,          
    Key_LEFT_SUPER,        
    Key_RIGHT_SHIFT,       
    Key_RIGHT_CONTROL,     
    Key_RIGHT_ALT,         
    Key_RIGHT_SUPER,       
    Key_MENU,              
};

enum class KeyModifier : uint8_t {
    Shift     = 1 << 0,
    Control   = 1 << 1,
    Alt       = 1 << 2,
    Super     = 1 << 3,
    CapsLock  = 1 << 4,
    NumLock   = 1 << 5,
};

class KeyModifierMask {
public:
    using underlying_t = uint8_t;

    constexpr KeyModifierMask() : mask(0) {}
    constexpr KeyModifierMask(KeyModifier mod) : mask(static_cast<underlying_t>(mod)) {}
    constexpr KeyModifierMask(underlying_t m) : mask(m) {}

    // Bitwise OR
    constexpr KeyModifierMask operator|(KeyModifier other) const {
        return KeyModifierMask(mask | static_cast<underlying_t>(other));
    }
    constexpr KeyModifierMask operator|(KeyModifierMask other) const {
        return KeyModifierMask(mask | other.mask);
    }
    KeyModifierMask& operator|=(KeyModifier other) {
        mask |= static_cast<underlying_t>(other);
        return *this;
    }
    KeyModifierMask& operator|=(KeyModifierMask other) {
        mask |= other.mask;
        return *this;
    }

    // Bitwise AND
    constexpr bool operator&(KeyModifier other) const {
        return (mask & static_cast<underlying_t>(other)) != 0;
    }
    constexpr bool operator&(KeyModifierMask other) const {
        return (mask & other.mask) != 0;
    }

    // Check if a modifier is set
    constexpr bool has(KeyModifier mod) const {
        return (mask & static_cast<underlying_t>(mod)) != 0;
    }

    // Get raw mask
    constexpr underlying_t value() const { return mask; }

private:
    underlying_t mask;
};

enum class MouseKeyCode : int
{
    UNDEFINED = 0,

    MouseKey_1,
    MouseKey_2,
    MouseKey_3,
    MouseKey_4,
    MouseKey_5,
    MouseKey_6,
    MouseKey_7,
    MouseKey_8,
};

};