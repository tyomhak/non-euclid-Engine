#pragma once

#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Window.h"
#include "EventHandler.h"


namespace ui
{

class UIWindow
{
public:
	UIWindow(Window* _window);
	virtual ~UIWindow();

	void Render();
	
protected:
	virtual void DefineWindow() = 0;

private:
	void Init();
	void Destruct();

private:
	const std::string glsl_version = "#version 130";
	ImGuiContext* _context;
	
protected:
	Window* _parent_window{nullptr};
};

}