#pragma once

#include "IncludeHeaders.h"
#include "UiWindow.h"

#include <string>
#include <vector>

class UI
{
public:
	UI(GLFWwindow* _window) :
		window(_window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		//createWindow("Window");
	}

	void createWindow(const char* name) 
	{
		ImGui::Begin(name);		
		ImGui::Button("Create");
		ImGui::End();
	}

	void run()
	{
		// feed inputs to dear imgui, start new frame
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		createWindow("Window");


		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

private:
	const char* glsl_version = "#version 130";
	std::vector<UiWindow*> uiWindows;
	GLFWwindow* window;
};
