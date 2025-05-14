#include "ui_layer.hpp"

#include <iostream>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "window_event.hpp"
#include "mouse_event.hpp"
#include "key_event.hpp"



namespace njin
{

UILayer::UILayer(Window* window) 
    : Layer("UILayer") 
    , _parent_window(window)
{
    Init(_parent_window);
}

UILayer::~UILayer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext((ImGuiContext*)_context);
}

void UILayer::Init(Window* window)
{
    assert(window != nullptr);
    IMGUI_CHECKVERSION();

    _context = (void*)ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->GetNativeWindow(), false);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void UILayer::OnAttach()
{

}

void UILayer::OnDetach()
{

}

void UILayer::OnUpdate()
{
    auto& io = ImGui::GetIO();
    io.DisplaySize = {(float)_parent_window->GetWidth(), (float)_parent_window->GetHeight()};

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static const std::string window_name{"Inspector"};

    auto window_flags = ImGuiWindowFlags_NoResize
            // | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_MenuBar;
    ImGui::SetNextWindowPos({0,0});
    ImGui::SetNextWindowSize({375.0f, 375.0f * 2.f});
    ImGui::Begin(window_name.c_str(), nullptr, window_flags);

    if (ImGui::Button("Temp", {100, 100}))
    {
        std::cout << "Something Clicked" << std::endl;
    }

    ImGui::End();
    

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UILayer::OnEvent(Event& e)
{
    auto& io = ImGui::GetIO();

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseMovedEvent>([&io](auto& event){
        io.AddMousePosEvent(event.GetXPosition(), event.GetYPosition());
        return true;
    });
    dispatcher.Dispatch<MouseKeyPressedEvent>([&io](auto& event){
        io.AddMouseButtonEvent(event.GetKeyCode(), true);
        return true;
    });
    dispatcher.Dispatch<MouseKeyReleasedEvent>([&io](auto& event){
        io.AddMouseButtonEvent(event.GetKeyCode(), false);
        return true;
    });
    dispatcher.Dispatch<MouseScrolledEvent>([&io](auto& event){
        io.AddMouseWheelEvent(event.GetXScroll(), event.GetYScroll());
        return true;
    });
    
    dispatcher.Dispatch<WindowFocusEvent>([&io](auto& event){
        io.AddFocusEvent(true);
        return true;
    });
    dispatcher.Dispatch<WindowLostFocusEvent>([&io](auto& event){
        io.AddFocusEvent(false);
        return true;
    });
    dispatcher.Dispatch<WindowMovedEvent>([&io](auto& event){
        // ImGui_Disp

        return true;
    });

    dispatcher.Dispatch<WindowResizeEvent>([&io](auto& event){
        io.DisplaySize = {(float)event.GetWidth(), (float)event.GetHeight()};
        return true;
    });

    dispatcher.Dispatch<KeyPressedEvent>([&io](auto& event){
        io.AddKeyEvent((ImGuiKey)event.GetKeyCode(), true);
        return true;
    });
    dispatcher.Dispatch<KeyReleasedEvent>([&io](auto& event){
        io.AddKeyEvent((ImGuiKey)event.GetKeyCode(), false);
        return true;
    });
}


}