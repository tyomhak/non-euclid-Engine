#pragma once

#include "IncludeHeaders.h"
#include "UiWindow.h"
#include "PositionUi.h"

#include <string>
#include <vector>

class UI
{
private:
	// attributes of buttons
	const char* objects_menu_items[4]{ "", "cube", "backpack", "portal" };
	int selected_object_item = 0;
	bool tabs_active = true;
	short tabs_index = 0;
	ImVec2 cursor_pos = { 0, 250 };	// make this dynamics later to set the cursor position once and forever


public:

	UI(GLFWwindow* _window, EventHandler* _eventHandler) :
		window(_window),
		eventHandler(_eventHandler)
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

	void createWindow(const char* window_name) 
	{
		// Create a window called "My First Tool", with a menu bar.
		ImGui::Begin(window_name, &tabs_active, ImGuiWindowFlags_MenuBar);

		// choosing object to be created
		ImGui::Combo("Choose object", &selected_object_item, objects_menu_items, IM_ARRAYSIZE(objects_menu_items));
		
		ImGui::Dummy(ImVec2(0.0f, 7.0f));	// adds horizontal and vertical spacing by mentioned size

		// adding tabs for object manipulations
		ImGui::Columns(4);
		if (ImGui::Button("Position")) tabs_index = 1;
		ImGui::NextColumn();
		if (ImGui::Button("Size")) tabs_index = 2;
		ImGui::NextColumn();
		if (ImGui::Button("Color")) tabs_index = 3;
		ImGui::NextColumn();
		if (ImGui::Button("Other")) tabs_index = 4;
		ImGui::Columns(1);
		ImGui::Separator();		// places a separator line

		if (tabs_index == 1)
		{
			PositionUi positionWindow("PositionWindow", eventHandler);
			positionWindow.render();
		}
		if (tabs_index == 2)
		{
			// stuff to be displayed in tab 1
			ImGui::Button("tab2 btn 1");
			ImGui::SameLine();
			ImGui::Button("tab2 btn 2");
		}
		if (tabs_index == 3)
		{
			ImGui::Begin("Object Color window");
			static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			ImGui::ColorEdit3("color1", color);							// color buttons (sliders R,G,B and button)
			ImGui::End();
		}
		if (tabs_index == 4)
		{
			ImGui::Begin("Object Movement window");
			// object movement handling
			static float direction[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			static float speed = 0.0f;

            ImGui::InputFloat3("input direction", direction);
			ImGui::SliderFloat("speed", &speed, 0.0f, 10.0f);
			
			ImGui::End();
		}

		ImGui::SetCursorPos(cursor_pos);	// places upcoming attributes of the window on the place that is set by cursor

		// Selected object status display
		ImGui::Text((" Update object ID: " + eventHandler->updateObjectId).c_str());
		ImGui::Text(("Under View object ID: " + eventHandler->underViewObjectId).c_str());


		// Save, Delete, Create functionality
		ImGui::Separator();
		ImGui::Spacing();ImGui::Spacing();	// can be replaced by ImGui::Dummy(ImVec2(0.0f, 2.0f));
		if (ImGui::Button("Delete"))
		{
			eventHandler->deleteObject();
		}

		ImGui::SameLine();
		ImGui::Dummy(ImVec2(200.0f, 0.0f));
		ImGui::SameLine();
		if (ImGui::Button("Create"))
		{
			if (objects_menu_items[selected_object_item] != "" && objects_menu_items[selected_object_item] != "portal")
			{
				eventHandler->creativeEnabled = true;
				glm::vec3 position = glm::vec3(-0.5f, 0.0f, 0.0f);
				eventHandler->updateObjectId = eventHandler->addObject(objects_menu_items[selected_object_item], position);	// add also the 'size' and 'color'
			}

			if (objects_menu_items[selected_object_item] == "portal")
			{
				eventHandler->addPortals();
			}
		}

		ImGui::SameLine();
		ImGui::Dummy(ImVec2(5.0f, 0.0f));
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			eventHandler->creativeEnabled = false;
			eventHandler->underViewObjectId = "None";
			eventHandler->updateObjectId = "None";
		}

		ImGui::End();
	}

	void render()
	{
		// feed inputs to dear imgui, start new frame
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		createWindow("Object Creation/Manipulation window");


		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

private:
	const char* glsl_version = "#version 130";
	std::vector<UiWindow*> uiWindows;
	GLFWwindow* window;
	EventHandler* eventHandler;
};
