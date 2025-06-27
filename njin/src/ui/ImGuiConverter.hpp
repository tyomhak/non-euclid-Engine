#pragma once

#include "key_codes.hpp"
#include "imgui.h"

#include <unordered_map>

namespace njin
{
namespace imgui
{

ImGuiKey ToImGuiKey(KeyCode keyCode)
{
    const static std::unordered_map<KeyCode, ImGuiKey> keysMap{
        { KeyCode::Key_UNDEFINED, ImGuiKey_None},
        { KeyCode::Key_SPACE, ImGuiKey_Space},             
        { KeyCode::Key_APOSTROPHE, ImGuiKey_Apostrophe},      
        { KeyCode::Key_COMMA, ImGuiKey_Comma},
        { KeyCode::Key_MINUS, ImGuiKey_Minus},      
        { KeyCode::Key_PERIOD, ImGuiKey_Period},      
        { KeyCode::Key_SLASH, ImGuiKey_Slash},    
        { KeyCode::Key_0, ImGuiKey_0},
        { KeyCode::Key_1, ImGuiKey_1},
        { KeyCode::Key_2, ImGuiKey_2},
        { KeyCode::Key_3, ImGuiKey_3},
        { KeyCode::Key_4, ImGuiKey_4},              
        { KeyCode::Key_5, ImGuiKey_5},
        { KeyCode::Key_6, ImGuiKey_6},
        { KeyCode::Key_7, ImGuiKey_7},
        { KeyCode::Key_8, ImGuiKey_8},
        { KeyCode::Key_9, ImGuiKey_9},
        { KeyCode::Key_SEMICOLON, ImGuiKey_Semicolon},
        { KeyCode::Key_EQUAL, ImGuiKey_Equal},
        { KeyCode::Key_A, ImGuiKey_A},
        { KeyCode::Key_B, ImGuiKey_B},
        { KeyCode::Key_C, ImGuiKey_C},
        { KeyCode::Key_D, ImGuiKey_D},
        { KeyCode::Key_E, ImGuiKey_E},
        { KeyCode::Key_F, ImGuiKey_F},
        { KeyCode::Key_G, ImGuiKey_G},
        { KeyCode::Key_H, ImGuiKey_H},
        { KeyCode::Key_I, ImGuiKey_I},
        { KeyCode::Key_J, ImGuiKey_J},
        { KeyCode::Key_K, ImGuiKey_K},
        { KeyCode::Key_L, ImGuiKey_L},
        { KeyCode::Key_M, ImGuiKey_M},
        { KeyCode::Key_N, ImGuiKey_N},
        { KeyCode::Key_O, ImGuiKey_O},
        { KeyCode::Key_P, ImGuiKey_P},
        { KeyCode::Key_Q, ImGuiKey_Q},
        { KeyCode::Key_R, ImGuiKey_R},
        { KeyCode::Key_S, ImGuiKey_S},
        { KeyCode::Key_T, ImGuiKey_T},
        { KeyCode::Key_U, ImGuiKey_U},
        { KeyCode::Key_V, ImGuiKey_V},
        { KeyCode::Key_W, ImGuiKey_W},
        { KeyCode::Key_X, ImGuiKey_X},
        { KeyCode::Key_Y, ImGuiKey_Y},
        { KeyCode::Key_Z, ImGuiKey_Z},
        { KeyCode::Key_LEFT_BRACKET, ImGuiKey_LeftBracket},
        { KeyCode::Key_BACKSLASH, ImGuiKey_Backslash},
        { KeyCode::Key_RIGHT_BRACKET, ImGuiKey_RightBracket},
        { KeyCode::Key_GRAVE_ACCENT, ImGuiKey_GraveAccent},
        // { KeyCode::Key_WORLD_1, 
        // { KeyCode::Key_WORLD_2,            
        { KeyCode::Key_ESCAPE, ImGuiKey_Escape},     
        { KeyCode::Key_ENTER, ImGuiKey_Enter},    
        { KeyCode::Key_TAB, ImGuiKey_Tab},      
        { KeyCode::Key_BACKSPACE, ImGuiKey_Backspace},
        { KeyCode::Key_INSERT, ImGuiKey_Insert},
        { KeyCode::Key_DELETE, ImGuiKey_Delete},
        { KeyCode::Key_RIGHT, ImGuiKey_RightArrow},    
        { KeyCode::Key_LEFT, ImGuiKey_LeftArrow}, 
        { KeyCode::Key_DOWN, ImGuiKey_DownArrow},   
        { KeyCode::Key_UP, ImGuiKey_UpArrow},   
        { KeyCode::Key_PAGE_UP, ImGuiKey_PageUp},       
        { KeyCode::Key_PAGE_DOWN, ImGuiKey_PageDown},   
        { KeyCode::Key_HOME, ImGuiKey_Home},
        { KeyCode::Key_END, ImGuiKey_End},        
        { KeyCode::Key_CAPS_LOCK, ImGuiKey_CapsLock},         
        { KeyCode::Key_SCROLL_LOCK, ImGuiKey_ScrollLock},
        { KeyCode::Key_NUM_LOCK, ImGuiKey_NumLock},
        { KeyCode::Key_PRINT_SCREEN, ImGuiKey_PrintScreen}, 
        { KeyCode::Key_PAUSE, ImGuiKey_Pause},
        { KeyCode::Key_F1, ImGuiKey_F1},    
        { KeyCode::Key_F2, ImGuiKey_F2},              
        { KeyCode::Key_F3, ImGuiKey_F3},              
        { KeyCode::Key_F4, ImGuiKey_F4},              
        { KeyCode::Key_F5, ImGuiKey_F5},              
        { KeyCode::Key_F6, ImGuiKey_F6},              
        { KeyCode::Key_F7, ImGuiKey_F7},              
        { KeyCode::Key_F8, ImGuiKey_F8},              
        { KeyCode::Key_F9, ImGuiKey_F9},              
        { KeyCode::Key_F10, ImGuiKey_F10},               
        { KeyCode::Key_F11, ImGuiKey_F11},               
        { KeyCode::Key_F12, ImGuiKey_F12},               
        { KeyCode::Key_F13, ImGuiKey_F13},               
        { KeyCode::Key_F14, ImGuiKey_F14},               
        { KeyCode::Key_F15, ImGuiKey_F15},               
        { KeyCode::Key_F16, ImGuiKey_F16},               
        { KeyCode::Key_F17, ImGuiKey_F17},               
        { KeyCode::Key_F18, ImGuiKey_F18},               
        { KeyCode::Key_F19, ImGuiKey_F19},               
        { KeyCode::Key_F20, ImGuiKey_F20},               
        { KeyCode::Key_F21, ImGuiKey_F21},               
        { KeyCode::Key_F22, ImGuiKey_F22},               
        { KeyCode::Key_F23, ImGuiKey_F23},               
        { KeyCode::Key_F24, ImGuiKey_F24},               
        // { KeyCode::Key_F25, ImGuiKey_F}, // ImGui does not have F25
        { KeyCode::Key_KP_0, ImGuiKey_Keypad0},              
        { KeyCode::Key_KP_1, ImGuiKey_Keypad1},              
        { KeyCode::Key_KP_2, ImGuiKey_Keypad2},              
        { KeyCode::Key_KP_3, ImGuiKey_Keypad3},              
        { KeyCode::Key_KP_4, ImGuiKey_Keypad4},              
        { KeyCode::Key_KP_5, ImGuiKey_Keypad5},              
        { KeyCode::Key_KP_6, ImGuiKey_Keypad6},              
        { KeyCode::Key_KP_7, ImGuiKey_Keypad7},              
        { KeyCode::Key_KP_8, ImGuiKey_Keypad8},              
        { KeyCode::Key_KP_9, ImGuiKey_Keypad9},              
        { KeyCode::Key_KP_DECIMAL, ImGuiKey_KeypadDecimal},        
        { KeyCode::Key_KP_DIVIDE, ImGuiKey_KeypadDivide},         
        { KeyCode::Key_KP_MULTIPLY, ImGuiKey_KeypadMultiply},       
        { KeyCode::Key_KP_SUBTRACT, ImGuiKey_KeypadSubtract},       
        { KeyCode::Key_KP_ADD, ImGuiKey_KeypadAdd},            
        { KeyCode::Key_KP_ENTER, ImGuiKey_KeypadEnter},          
        { KeyCode::Key_KP_EQUAL, ImGuiKey_KeypadEqual},          
        { KeyCode::Key_LEFT_SHIFT, ImGuiKey_LeftShift},        
        { KeyCode::Key_LEFT_CONTROL, ImGuiKey_LeftCtrl},      
        { KeyCode::Key_LEFT_ALT, ImGuiKey_LeftAlt},          
        { KeyCode::Key_LEFT_SUPER, ImGuiKey_LeftSuper},        
        { KeyCode::Key_RIGHT_SHIFT, ImGuiKey_RightShift},       
        { KeyCode::Key_RIGHT_CONTROL, ImGuiKey_RightCtrl},     
        { KeyCode::Key_RIGHT_ALT, ImGuiKey_RightAlt},         
        { KeyCode::Key_RIGHT_SUPER, ImGuiKey_RightSuper},       
        { KeyCode::Key_MENU, ImGuiKey_Menu} 
    };

    return keysMap.contains(keyCode) ? keysMap.at(keyCode) : ImGuiKey_None;
};

int ToImGuiKeyMod(KeyModifierMask modifierMask)
{
    int mods = ImGuiKey_None;
    if (modifierMask.has(KeyModifier::Shift))
        mods |= ImGuiMod_Shift;
    if (modifierMask.has(KeyModifier::Control))
        mods |= ImGuiMod_Ctrl;
    if (modifierMask.has(KeyModifier::Alt))
        mods |= ImGuiMod_Alt;
    if (modifierMask.has(KeyModifier::Super))
        mods |= ImGuiMod_Super;
    return mods;
}

ImGuiMouseButton_ ToImGuiMouseKey(MouseKeyCode key)
{
    const static std::unordered_map<MouseKeyCode, ImGuiMouseButton_> keysMap {
        {MouseKeyCode::MouseKey_1, ImGuiMouseButton_Left },
        {MouseKeyCode::MouseKey_2, ImGuiMouseButton_Right },
        {MouseKeyCode::MouseKey_3, ImGuiMouseButton_Middle },
        // {MouseKeyCode::MouseKey_4, ImGuiMouseButton },
        // {MouseKeyCode::MouseKey_5, ImGuiMouseButton },
        // {MouseKeyCode::MouseKey_6, ImGuiMouseButton },
        // {MouseKeyCode::MouseKey_7, ImGuiMouseButton },
        // {MouseKeyCode::MouseKey_8, ImGuiMouseButton },
    };

    return keysMap.contains(key) ? keysMap.at(key) : ImGuiMouseButton_COUNT;
}

};
};