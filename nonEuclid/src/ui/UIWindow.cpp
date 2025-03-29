#include "UIWindow.h"

using namespace ui;

UIWindow::UIWindow(Window* _window) 
    : _parent_window(_window)
{
    assert(_window != nullptr);

    IMGUI_CHECKVERSION();
    _context = ImGui::CreateContext();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(_parent_window->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());

    ImGui::StyleColorsDark();
}

UIWindow::~UIWindow()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(_context);
}

void UIWindow::_CreateWindow(const char* window_name) 
{
    // Create a window called "My First Tool", with a menu bar.
    auto window_flags = ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_MenuBar;
    ImGui::SetNextWindowPos({0,0});
    ImGui::SetNextWindowSize({360.0f, (float)_parent_window->GetHeight()});
    ImGui::Begin(window_name, &tabs_active, window_flags);

    _DefineWindowContent();

    ImGui::End(); 
}

void UIWindow::Render()
{
    // ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    _CreateWindow(_window_title.c_str());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}