#include "input.hpp"

namespace njin
{

bool Input::IsKeyPressed(KeyCode key) 
{ 
    return Application::Get()->GetMainWindow()->GetInputPoller()->IsKeyPressed(key); 
};

bool Input::IsMouseButtonPressed(MouseKeyCode mouseButton) 
{ 
    return Application::Get()->GetMainWindow()->GetInputPoller()->IsMouseButtonPressed(mouseButton); 
};

Point Input::GetMousePosition() 
{ 
    return Application::Get()->GetMainWindow()->GetInputPoller()->GetMousePosition(); 
};

};