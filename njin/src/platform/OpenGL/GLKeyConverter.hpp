#pragma once

#include "key_codes.hpp"
#include <GLFW/glfw3.h>

#include <unordered_map>

namespace njin
{
namespace open_gl
{

KeyCode ToKeyCode(int glKey)
{
    const static std::unordered_map<int, KeyCode> keys_map {
        { GLFW_KEY_SPACE          , KeyCode::Key_SPACE},             
        { GLFW_KEY_APOSTROPHE     , KeyCode::Key_APOSTROPHE},        
        { GLFW_KEY_COMMA          , KeyCode::Key_COMMA},             
        { GLFW_KEY_MINUS          , KeyCode::Key_MINUS},             
        { GLFW_KEY_PERIOD         , KeyCode::Key_PERIOD},            
        { GLFW_KEY_SLASH          , KeyCode::Key_SLASH},             
        { GLFW_KEY_0              , KeyCode::Key_0},                 
        { GLFW_KEY_1              , KeyCode::Key_1},                 
        { GLFW_KEY_2              , KeyCode::Key_2},                 
        { GLFW_KEY_3              , KeyCode::Key_3},                 
        { GLFW_KEY_4              , KeyCode::Key_4},                 
        { GLFW_KEY_5              , KeyCode::Key_5},                 
        { GLFW_KEY_6              , KeyCode::Key_6},                 
        { GLFW_KEY_7              , KeyCode::Key_7},                 
        { GLFW_KEY_8              , KeyCode::Key_8},                 
        { GLFW_KEY_9              , KeyCode::Key_9},                 
        { GLFW_KEY_SEMICOLON      , KeyCode::Key_SEMICOLON},         
        { GLFW_KEY_EQUAL          , KeyCode::Key_EQUAL},             
        { GLFW_KEY_A              , KeyCode::Key_A},                 
        { GLFW_KEY_B              , KeyCode::Key_B},                 
        { GLFW_KEY_C              , KeyCode::Key_C},                 
        { GLFW_KEY_D              , KeyCode::Key_D},                 
        { GLFW_KEY_E              , KeyCode::Key_E},                 
        { GLFW_KEY_F              , KeyCode::Key_F},                 
        { GLFW_KEY_G              , KeyCode::Key_G},                 
        { GLFW_KEY_H              , KeyCode::Key_H},                 
        { GLFW_KEY_I              , KeyCode::Key_I},                 
        { GLFW_KEY_J              , KeyCode::Key_J},                 
        { GLFW_KEY_K              , KeyCode::Key_K},                 
        { GLFW_KEY_L              , KeyCode::Key_L},                 
        { GLFW_KEY_M              , KeyCode::Key_M},                 
        { GLFW_KEY_N              , KeyCode::Key_N},                 
        { GLFW_KEY_O              , KeyCode::Key_O},                 
        { GLFW_KEY_P              , KeyCode::Key_P},                 
        { GLFW_KEY_Q              , KeyCode::Key_Q},                 
        { GLFW_KEY_R              , KeyCode::Key_R},                 
        { GLFW_KEY_S              , KeyCode::Key_S},                 
        { GLFW_KEY_T              , KeyCode::Key_T},                 
        { GLFW_KEY_U              , KeyCode::Key_U},                 
        { GLFW_KEY_V              , KeyCode::Key_V},                 
        { GLFW_KEY_W              , KeyCode::Key_W},                 
        { GLFW_KEY_X              , KeyCode::Key_X},                 
        { GLFW_KEY_Y              , KeyCode::Key_Y},                 
        { GLFW_KEY_Z              , KeyCode::Key_Z},                 
        { GLFW_KEY_LEFT_BRACKET   , KeyCode::Key_LEFT_BRACKET},      
        { GLFW_KEY_BACKSLASH      , KeyCode::Key_BACKSLASH},         
        { GLFW_KEY_RIGHT_BRACKET  , KeyCode::Key_RIGHT_BRACKET},     
        { GLFW_KEY_GRAVE_ACCENT   , KeyCode::Key_GRAVE_ACCENT},      
        { GLFW_KEY_WORLD_1        , KeyCode::Key_WORLD_1},           
        { GLFW_KEY_WORLD_2        , KeyCode::Key_WORLD_2},

        { GLFW_KEY_ESCAPE          , KeyCode::Key_ESCAPE},            
        { GLFW_KEY_ENTER           , KeyCode::Key_ENTER},             
        { GLFW_KEY_TAB             , KeyCode::Key_TAB},               
        { GLFW_KEY_BACKSPACE       , KeyCode::Key_BACKSPACE},         
        { GLFW_KEY_INSERT          , KeyCode::Key_INSERT},            
        { GLFW_KEY_DELETE          , KeyCode::Key_DELETE},            
        { GLFW_KEY_RIGHT           , KeyCode::Key_RIGHT},             
        { GLFW_KEY_LEFT            , KeyCode::Key_LEFT},              
        { GLFW_KEY_DOWN            , KeyCode::Key_DOWN},              
        { GLFW_KEY_UP              , KeyCode::Key_UP},                
        { GLFW_KEY_PAGE_UP         , KeyCode::Key_PAGE_UP},           
        { GLFW_KEY_PAGE_DOWN       , KeyCode::Key_PAGE_DOWN},         
        { GLFW_KEY_HOME            , KeyCode::Key_HOME},              
        { GLFW_KEY_END             , KeyCode::Key_END},               
        { GLFW_KEY_CAPS_LOCK       , KeyCode::Key_CAPS_LOCK},         
        { GLFW_KEY_SCROLL_LOCK     , KeyCode::Key_SCROLL_LOCK},       
        { GLFW_KEY_NUM_LOCK        , KeyCode::Key_NUM_LOCK},          
        { GLFW_KEY_PRINT_SCREEN    , KeyCode::Key_PRINT_SCREEN},      
        { GLFW_KEY_PAUSE           , KeyCode::Key_PAUSE},             
        { GLFW_KEY_F1              , KeyCode::Key_F1},                
        { GLFW_KEY_F2              , KeyCode::Key_F2},                
        { GLFW_KEY_F3              , KeyCode::Key_F3},                
        { GLFW_KEY_F4              , KeyCode::Key_F4},                
        { GLFW_KEY_F5              , KeyCode::Key_F5},                
        { GLFW_KEY_F6              , KeyCode::Key_F6},                
        { GLFW_KEY_F7              , KeyCode::Key_F7},                
        { GLFW_KEY_F8              , KeyCode::Key_F8},                
        { GLFW_KEY_F9              , KeyCode::Key_F9},                
        { GLFW_KEY_F10             , KeyCode::Key_F10},               
        { GLFW_KEY_F11             , KeyCode::Key_F11},               
        { GLFW_KEY_F12             , KeyCode::Key_F12},               
        { GLFW_KEY_F13             , KeyCode::Key_F13},               
        { GLFW_KEY_F14             , KeyCode::Key_F14},               
        { GLFW_KEY_F15             , KeyCode::Key_F15},               
        { GLFW_KEY_F16             , KeyCode::Key_F16},               
        { GLFW_KEY_F17             , KeyCode::Key_F17},               
        { GLFW_KEY_F18             , KeyCode::Key_F18},               
        { GLFW_KEY_F19             , KeyCode::Key_F19},               
        { GLFW_KEY_F20             , KeyCode::Key_F20},               
        { GLFW_KEY_F21             , KeyCode::Key_F21},               
        { GLFW_KEY_F22             , KeyCode::Key_F22},               
        { GLFW_KEY_F23             , KeyCode::Key_F23},               
        { GLFW_KEY_F24             , KeyCode::Key_F24},               
        { GLFW_KEY_F25             , KeyCode::Key_F25},               
        { GLFW_KEY_KP_0            , KeyCode::Key_KP_0},              
        { GLFW_KEY_KP_1            , KeyCode::Key_KP_1},              
        { GLFW_KEY_KP_2            , KeyCode::Key_KP_2},              
        { GLFW_KEY_KP_3            , KeyCode::Key_KP_3},              
        { GLFW_KEY_KP_4            , KeyCode::Key_KP_4},              
        { GLFW_KEY_KP_5            , KeyCode::Key_KP_5},              
        { GLFW_KEY_KP_6            , KeyCode::Key_KP_6},              
        { GLFW_KEY_KP_7            , KeyCode::Key_KP_7},              
        { GLFW_KEY_KP_8            , KeyCode::Key_KP_8},              
        { GLFW_KEY_KP_9            , KeyCode::Key_KP_9},              
        { GLFW_KEY_KP_DECIMAL      , KeyCode::Key_KP_DECIMAL},        
        { GLFW_KEY_KP_DIVIDE       , KeyCode::Key_KP_DIVIDE},         
        { GLFW_KEY_KP_MULTIPLY     , KeyCode::Key_KP_MULTIPLY},       
        { GLFW_KEY_KP_SUBTRACT     , KeyCode::Key_KP_SUBTRACT},       
        { GLFW_KEY_KP_ADD          , KeyCode::Key_KP_ADD},            
        { GLFW_KEY_KP_ENTER        , KeyCode::Key_KP_ENTER},          
        { GLFW_KEY_KP_EQUAL        , KeyCode::Key_KP_EQUAL},          
        { GLFW_KEY_LEFT_SHIFT      , KeyCode::Key_LEFT_SHIFT},        
        { GLFW_KEY_LEFT_CONTROL    , KeyCode::Key_LEFT_CONTROL},      
        { GLFW_KEY_LEFT_ALT        , KeyCode::Key_LEFT_ALT},          
        { GLFW_KEY_LEFT_SUPER      , KeyCode::Key_LEFT_SUPER},        
        { GLFW_KEY_RIGHT_SHIFT     , KeyCode::Key_RIGHT_SHIFT},       
        { GLFW_KEY_RIGHT_CONTROL   , KeyCode::Key_RIGHT_CONTROL},     
        { GLFW_KEY_RIGHT_ALT       , KeyCode::Key_RIGHT_ALT},         
        { GLFW_KEY_RIGHT_SUPER     , KeyCode::Key_RIGHT_SUPER},       
        { GLFW_KEY_MENU            , KeyCode::Key_MENU},
    };

    if (keys_map.contains(glKey))
        return keys_map.at(glKey);
    
    return KeyCode::Key_UNDEFINED;
}


constexpr uint8_t glfwToKeyModifierMask(int glfwMods) {
    constexpr uint8_t mask =
        GLFW_MOD_SHIFT |
        GLFW_MOD_CONTROL |
        GLFW_MOD_ALT |
        GLFW_MOD_SUPER |
        GLFW_MOD_CAPS_LOCK |
        GLFW_MOD_NUM_LOCK;
    return static_cast<uint8_t>(glfwMods & mask);
}
inline KeyModifierMask glfwModsToKeyModifierMask(int glfwMods) {
    return KeyModifierMask(glfwToKeyModifierMask(glfwMods));
}

MouseKeyCode ToMouseKey(int glKey)
{
    const static std::unordered_map<int, MouseKeyCode> mouseKeysMap {
        { GLFW_MOUSE_BUTTON_1, MouseKeyCode::MouseKey_1},
        { GLFW_MOUSE_BUTTON_2, MouseKeyCode::MouseKey_2},
        { GLFW_MOUSE_BUTTON_3, MouseKeyCode::MouseKey_3},
        { GLFW_MOUSE_BUTTON_4, MouseKeyCode::MouseKey_4},
        { GLFW_MOUSE_BUTTON_5, MouseKeyCode::MouseKey_5},
        { GLFW_MOUSE_BUTTON_6, MouseKeyCode::MouseKey_6},
        { GLFW_MOUSE_BUTTON_7, MouseKeyCode::MouseKey_7},
        { GLFW_MOUSE_BUTTON_8, MouseKeyCode::MouseKey_8},
    };

    return mouseKeysMap.contains(glKey) ? mouseKeysMap.at(glKey) : MouseKeyCode::UNDEFINED;
}


int ToGLFWKeyCode(KeyCode key)
{
    const static std::unordered_map<KeyCode, int> keys_map {
        { KeyCode::Key_SPACE, GLFW_KEY_SPACE },             
        { KeyCode::Key_APOSTROPHE, GLFW_KEY_APOSTROPHE },        
        { KeyCode::Key_COMMA, GLFW_KEY_COMMA },             
        { KeyCode::Key_MINUS, GLFW_KEY_MINUS },             
        { KeyCode::Key_PERIOD, GLFW_KEY_PERIOD },            
        { KeyCode::Key_SLASH, GLFW_KEY_SLASH },             
        { KeyCode::Key_0, GLFW_KEY_0 },                 
        { KeyCode::Key_1, GLFW_KEY_1 },                 
        { KeyCode::Key_2, GLFW_KEY_2 },                 
        { KeyCode::Key_3, GLFW_KEY_3 },                 
        { KeyCode::Key_4, GLFW_KEY_4 },                 
        { KeyCode::Key_5, GLFW_KEY_5 },                 
        { KeyCode::Key_6, GLFW_KEY_6 },                 
        { KeyCode::Key_7, GLFW_KEY_7 },                 
        { KeyCode::Key_8, GLFW_KEY_8 },                 
        { KeyCode::Key_9, GLFW_KEY_9 },                 
        { KeyCode::Key_SEMICOLON, GLFW_KEY_SEMICOLON },         
        { KeyCode::Key_EQUAL, GLFW_KEY_EQUAL },             
        { KeyCode::Key_A, GLFW_KEY_A },                 
        { KeyCode::Key_B, GLFW_KEY_B },                 
        { KeyCode::Key_C, GLFW_KEY_C },                 
        { KeyCode::Key_D, GLFW_KEY_D },                 
        { KeyCode::Key_E, GLFW_KEY_E },                 
        { KeyCode::Key_F, GLFW_KEY_F },                 
        { KeyCode::Key_G, GLFW_KEY_G },                 
        { KeyCode::Key_H, GLFW_KEY_H },                 
        { KeyCode::Key_I, GLFW_KEY_I },                 
        { KeyCode::Key_J, GLFW_KEY_J },                 
        { KeyCode::Key_K, GLFW_KEY_K },                 
        { KeyCode::Key_L, GLFW_KEY_L },                 
        { KeyCode::Key_M, GLFW_KEY_M },                 
        { KeyCode::Key_N, GLFW_KEY_N },                 
        { KeyCode::Key_O, GLFW_KEY_O },                 
        { KeyCode::Key_P, GLFW_KEY_P },                 
        { KeyCode::Key_Q, GLFW_KEY_Q },                 
        { KeyCode::Key_R, GLFW_KEY_R },                 
        { KeyCode::Key_S, GLFW_KEY_S },                 
        { KeyCode::Key_T, GLFW_KEY_T },                 
        { KeyCode::Key_U, GLFW_KEY_U },                 
        { KeyCode::Key_V, GLFW_KEY_V },                 
        { KeyCode::Key_W, GLFW_KEY_W },                 
        { KeyCode::Key_X, GLFW_KEY_X },                 
        { KeyCode::Key_Y, GLFW_KEY_Y },                 
        { KeyCode::Key_Z, GLFW_KEY_Z },                 
        { KeyCode::Key_LEFT_BRACKET, GLFW_KEY_LEFT_BRACKET },      
        { KeyCode::Key_BACKSLASH, GLFW_KEY_BACKSLASH },         
        { KeyCode::Key_RIGHT_BRACKET, GLFW_KEY_RIGHT_BRACKET },     
        { KeyCode::Key_GRAVE_ACCENT, GLFW_KEY_GRAVE_ACCENT },      
        { KeyCode::Key_WORLD_1, GLFW_KEY_WORLD_1 },           
        { KeyCode::Key_WORLD_2, GLFW_KEY_WORLD_2 },
        { KeyCode::Key_ESCAPE, GLFW_KEY_ESCAPE },            
        { KeyCode::Key_ENTER, GLFW_KEY_ENTER },             
        { KeyCode::Key_TAB, GLFW_KEY_TAB },               
        { KeyCode::Key_BACKSPACE, GLFW_KEY_BACKSPACE },         
        { KeyCode::Key_INSERT, GLFW_KEY_INSERT },            
        { KeyCode::Key_DELETE, GLFW_KEY_DELETE },            
        { KeyCode::Key_RIGHT, GLFW_KEY_RIGHT },             
        { KeyCode::Key_LEFT, GLFW_KEY_LEFT },              
        { KeyCode::Key_DOWN, GLFW_KEY_DOWN },              
        { KeyCode::Key_UP, GLFW_KEY_UP },                
        { KeyCode::Key_PAGE_UP, GLFW_KEY_PAGE_UP },           
        { KeyCode::Key_PAGE_DOWN, GLFW_KEY_PAGE_DOWN },         
        { KeyCode::Key_HOME, GLFW_KEY_HOME },              
        { KeyCode::Key_END, GLFW_KEY_END },               
        { KeyCode::Key_CAPS_LOCK, GLFW_KEY_CAPS_LOCK },         
        { KeyCode::Key_SCROLL_LOCK, GLFW_KEY_SCROLL_LOCK },       
        { KeyCode::Key_NUM_LOCK, GLFW_KEY_NUM_LOCK },          
        { KeyCode::Key_PRINT_SCREEN, GLFW_KEY_PRINT_SCREEN },      
        { KeyCode::Key_PAUSE, GLFW_KEY_PAUSE },             
        { KeyCode::Key_F1, GLFW_KEY_F1 },                
        { KeyCode::Key_F2, GLFW_KEY_F2 },                
        { KeyCode::Key_F3, GLFW_KEY_F3 },                
        { KeyCode::Key_F4, GLFW_KEY_F4 },                
        { KeyCode::Key_F5, GLFW_KEY_F5 },                
        { KeyCode::Key_F6, GLFW_KEY_F6 },                
        { KeyCode::Key_F7, GLFW_KEY_F7 },                
        { KeyCode::Key_F8, GLFW_KEY_F8 },                
        { KeyCode::Key_F9, GLFW_KEY_F9 },                
        { KeyCode::Key_F10, GLFW_KEY_F10 },               
        { KeyCode::Key_F11, GLFW_KEY_F11 },               
        { KeyCode::Key_F12, GLFW_KEY_F12 },               
        { KeyCode::Key_F13, GLFW_KEY_F13 },               
        { KeyCode::Key_F14, GLFW_KEY_F14 },               
        { KeyCode::Key_F15, GLFW_KEY_F15 },               
        { KeyCode::Key_F16, GLFW_KEY_F16 },               
        { KeyCode::Key_F17, GLFW_KEY_F17 },               
        { KeyCode::Key_F18, GLFW_KEY_F18 },               
        { KeyCode::Key_F19, GLFW_KEY_F19 },               
        { KeyCode::Key_F20, GLFW_KEY_F20 },               
        { KeyCode::Key_F21, GLFW_KEY_F21 },               
        { KeyCode::Key_F22, GLFW_KEY_F22 },               
        { KeyCode::Key_F23, GLFW_KEY_F23 },               
        { KeyCode::Key_F24, GLFW_KEY_F24 },               
        { KeyCode::Key_F25, GLFW_KEY_F25 },               
        { KeyCode::Key_KP_0, GLFW_KEY_KP_0 },              
        { KeyCode::Key_KP_1, GLFW_KEY_KP_1 },              
        { KeyCode::Key_KP_2, GLFW_KEY_KP_2 },              
        { KeyCode::Key_KP_3, GLFW_KEY_KP_3 },              
        { KeyCode::Key_KP_4, GLFW_KEY_KP_4 },              
        { KeyCode::Key_KP_5, GLFW_KEY_KP_5 },              
        { KeyCode::Key_KP_6, GLFW_KEY_KP_6 },              
        { KeyCode::Key_KP_7, GLFW_KEY_KP_7 },              
        { KeyCode::Key_KP_8, GLFW_KEY_KP_8 },              
        { KeyCode::Key_KP_9, GLFW_KEY_KP_9 },              
        { KeyCode::Key_KP_DECIMAL, GLFW_KEY_KP_DECIMAL },        
        { KeyCode::Key_KP_DIVIDE, GLFW_KEY_KP_DIVIDE },         
        { KeyCode::Key_KP_MULTIPLY, GLFW_KEY_KP_MULTIPLY },       
        { KeyCode::Key_KP_SUBTRACT, GLFW_KEY_KP_SUBTRACT },       
        { KeyCode::Key_KP_ADD, GLFW_KEY_KP_ADD },            
        { KeyCode::Key_KP_ENTER, GLFW_KEY_KP_ENTER },          
        { KeyCode::Key_KP_EQUAL, GLFW_KEY_KP_EQUAL },          
        { KeyCode::Key_LEFT_SHIFT, GLFW_KEY_LEFT_SHIFT },        
        { KeyCode::Key_LEFT_CONTROL, GLFW_KEY_LEFT_CONTROL },      
        { KeyCode::Key_LEFT_ALT, GLFW_KEY_LEFT_ALT },          
        { KeyCode::Key_LEFT_SUPER, GLFW_KEY_LEFT_SUPER },        
        { KeyCode::Key_RIGHT_SHIFT, GLFW_KEY_RIGHT_SHIFT },       
        { KeyCode::Key_RIGHT_CONTROL, GLFW_KEY_RIGHT_CONTROL },     
        { KeyCode::Key_RIGHT_ALT, GLFW_KEY_RIGHT_ALT },         
        { KeyCode::Key_RIGHT_SUPER, GLFW_KEY_RIGHT_SUPER },       
        { KeyCode::Key_MENU, GLFW_KEY_MENU },
    };

    if (keys_map.contains(key))
        return keys_map.at(key);
    
    return GLFW_KEY_UNKNOWN;
}

int ToGLFWMouseKey(MouseKeyCode mouseKey)
{
    const static std::unordered_map<MouseKeyCode, int> mouseKeysMap {
        { MouseKeyCode::MouseKey_1, GLFW_MOUSE_BUTTON_1},
        { MouseKeyCode::MouseKey_2, GLFW_MOUSE_BUTTON_2},
        { MouseKeyCode::MouseKey_3, GLFW_MOUSE_BUTTON_3},
        { MouseKeyCode::MouseKey_4, GLFW_MOUSE_BUTTON_4},
        { MouseKeyCode::MouseKey_5, GLFW_MOUSE_BUTTON_5},
        { MouseKeyCode::MouseKey_6, GLFW_MOUSE_BUTTON_6},
        { MouseKeyCode::MouseKey_7, GLFW_MOUSE_BUTTON_7},
        { MouseKeyCode::MouseKey_8, GLFW_MOUSE_BUTTON_8},
    };
    

    return mouseKeysMap.contains(mouseKey) ? mouseKeysMap.at(mouseKey) : GLFW_KEY_UNKNOWN;
}

};
};