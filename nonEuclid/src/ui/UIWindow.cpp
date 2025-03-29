#include "UIWindow.h"

using namespace ui;

UIWindow::UIWindow(Window* window) 
    : _parent_window(window)
{
    Init();
}

UIWindow::~UIWindow()
{
    Destruct();
}

void UIWindow::Render()
{
    // ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    DefineWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIWindow::Init()
{
    assert(_parent_window != nullptr);

    IMGUI_CHECKVERSION();
    _context = ImGui::CreateContext();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(_parent_window->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());
}

void UIWindow::Destruct()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(_context);
}