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
	
private:
	void _CreateWindow(const char* window_name);

protected:
	virtual void _DefineWindowContent() = 0;

private:
	const std::string glsl_version = "#version 130";
	ImGuiContext* _context;	
	Window* _parent_window{nullptr};

	bool tabs_active = true;

protected:
	std::string _window_title{};
};

}