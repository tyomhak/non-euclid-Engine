#include "ui_layer.hpp"

#include <iostream>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "window_event.hpp"
#include "mouse_event.hpp"
#include "key_event.hpp"
#include "ImGuiConverter.hpp"

#include "input.hpp"

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

    auto& io = ImGui::GetIO();
    io.DisplaySize = { 0,0 };
}

void UILayer::OnAttach()
{

}

void UILayer::OnDetach()
{

}

void UILayer::OnUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    if (Input::IsKeyPressed(KeyCode::Key_TAB))
    {
        static const std::string window_name{"Inspector"};
        auto window_flags = ImGuiWindowFlags_NoResize
                // | ImGuiWindowFlags_NoCollapse
                | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_MenuBar;
        ImGui::SetNextWindowPos({0,0});
        ImGui::SetNextWindowSize({375.0f, 375.0f * 2.f});
        ImGui::Begin(window_name.c_str(), nullptr, window_flags);

        if (ImGui::Button("Temp", {100, 35}))
        {
            Logger::Log("Something Clicked");
        }
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UILayer::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseMovedEvent>([this](auto& event){ return OnMouseMovedEvent(event);});
    dispatcher.Dispatch<MouseKeyPressedEvent>([this](auto& event){ return OnMouseKeyPressedEvent(event);});
    dispatcher.Dispatch<MouseKeyReleasedEvent>([this](auto& event){ return OnMouseKeyReleasedEvent(event);});
    dispatcher.Dispatch<MouseScrolledEvent>([this](auto& event){ return OnMouseScrolledEvent(event);});

    dispatcher.Dispatch<WindowFocusEvent>([this](auto& event){ return OnWindowFocusEvent(event);});
    dispatcher.Dispatch<WindowLostFocusEvent>([this](auto& event){ return OnWindowLostFocusEvent(event);});
    dispatcher.Dispatch<WindowMovedEvent>([this](auto& event){ return OnWindowMovedEvent(event);});
    dispatcher.Dispatch<WindowResizeEvent>([this](auto& event){ return OnWindowResizeEvent(event);});

    dispatcher.Dispatch<KeyPressedEvent>([this](auto& event){ return OnKeyPressedEvent(event);});
    dispatcher.Dispatch<KeyReleasedEvent>([this](auto& event){ return OnKeyReleasedEvent(event);});
}

bool UILayer::OnMouseMovedEvent(MouseMovedEvent& event)
{
    auto& io = ImGui::GetIO();
    io.AddMousePosEvent(event.GetXPosition(), event.GetYPosition());
    return false;
}

bool UILayer::OnMouseKeyPressedEvent(MouseKeyPressedEvent& event)
{
    auto& io = ImGui::GetIO();
    io.AddMouseButtonEvent(static_cast<int>(imgui::ToImGuiMouseKey(event.GetKeyCode())), true);
    return false;
}

bool UILayer::OnMouseKeyReleasedEvent(MouseKeyReleasedEvent& event)
{
    auto& io = ImGui::GetIO();
    io.AddMouseButtonEvent((int)imgui::ToImGuiMouseKey(event.GetKeyCode()), false);
    return false;
}

bool UILayer::OnMouseScrolledEvent(MouseScrolledEvent& event)
{
    auto& io = ImGui::GetIO();
    io.AddMouseWheelEvent(event.GetXScroll(), event.GetYScroll());
    return false;
}

bool UILayer::OnWindowFocusEvent(WindowFocusEvent& event)
{
    auto& io = ImGui::GetIO();
    io.AddFocusEvent(true);
    return false;
}

bool UILayer::OnWindowLostFocusEvent(WindowLostFocusEvent& event)
{
    auto& io = ImGui::GetIO();
    io.AddFocusEvent(false);
    return false;
}

bool UILayer::OnWindowMovedEvent(WindowMovedEvent& event)
{
    // auto& io = ImGui::GetIO();

    return false;
}

bool UILayer::OnWindowResizeEvent(WindowResizeEvent& event)
{
    auto& io = ImGui::GetIO();
    io.DisplaySize = {(float)event.GetWidth(), (float)event.GetHeight()};
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    // glViewport(0, 0, event.GetWidth(), event.GetHeight());

    return false;
}

bool UILayer::OnKeyPressedEvent(KeyPressedEvent& event)
{
    auto& io = ImGui::GetIO();
    io.AddKeyEvent(imgui::ToImGuiKey(event.GetKeyCode()), true);
    return false;
}

bool UILayer::OnKeyReleasedEvent(KeyReleasedEvent& event)
{
    auto& io = ImGui::GetIO();
    io.AddKeyEvent(imgui::ToImGuiKey(event.GetKeyCode()), false);
    return false;
}



}