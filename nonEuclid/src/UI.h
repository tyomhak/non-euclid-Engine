#pragma once

#include <string>
#include <vector>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


class UI
{
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
		ImGui_ImplOpenGL3_Init(glsl_version.c_str());
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		//createWindow("Window");
	}

	void CreateWindow(const char* window_name) 
	{
		// Create a window called "My First Tool", with a menu bar.
		ImGui::Begin(window_name, &tabs_active, ImGuiWindowFlags_MenuBar);

		ImGui::SameLine(ImGui::GetWindowWidth() - 60.0f);		// adds next functionality on the same line with RightAline

		// helper button to get instructions
		if (ImGui::Button("Help")) { helper_window_active = !helper_window_active; }
		// helper window creation
		if (helper_window_active)
		{
			ImGui::Begin("Helper: instructions");	// open new table of instructions
			ImGui::BeginChild("Scrolling");			// enable scrolling in the window
			ImGui::BeginTable("Instructions", 1);	// create single table of values
			
			for (const auto &[key, description] : help_table)
			{
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(key.c_str());

				ImGui::SameLine(80.0f);
				ImGui::Text("--");

				ImGui::SameLine(120.0f);
				ImGui::Text(description.c_str());
			};

			ImGui::EndTable();
			ImGui::EndChild();
			ImGui::End();
		}


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
		ImGui::Separator();					// places a separator line

		// tabs attributes display
		if (tabs_index > 0)
		{
			ImGui::Text("Tab's functional is not implemented, yet.");
			ImGui::Text("Functional will be added with next releases.");
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
			eventHandler->DeleteObject();
		}

		ImGui::SameLine(ImGui::GetWindowWidth() - 130.0f);
		if (ImGui::Button("Create"))
		{
			if (objects_menu_items[selected_object_item] != "" && objects_menu_items[selected_object_item] != "portal")
			{
				eventHandler->creativeEnabled = true;
				glm::vec3 position = glm::vec3(-0.5f, 0.0f, 0.0f);
				eventHandler->updateObjectId = eventHandler->AddObject(objects_menu_items[selected_object_item], position);	// add also the 'size' and 'color'
			}

			if (objects_menu_items[selected_object_item] == "portal")
			{
				Portal::portalBackground[0] = 0.3f;
				Portal::portalBackground[1] = 0.8f;
				Portal::portalBackground[2] = 1.0f;
				eventHandler->AddPortals();
			}
		}

		ImGui::SameLine(ImGui::GetWindowWidth() - 60.0f);
		if (ImGui::Button("Save"))
		{
			eventHandler->creativeEnabled = false;
			eventHandler->underViewObjectId = "None";
			eventHandler->updateObjectId = "None";
		}

		ImGui::End();
	}

	void Render()
	{
		// feed inputs to dear imgui, start new frame
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		CreateWindow("Object Creation/Manipulation window");


		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

private:
	const std::string glsl_version = "#version 130";
	GLFWwindow* window;
	Window* _parent_window{nullptr};
	EventHandler* eventHandler;

	// attributes of buttons
	const char* objects_menu_items[4]{ "", "cube", "backpack", "portal" };
	int selected_object_item = 0;
	bool tabs_active = true;
	bool helper_window_active = false;
	short tabs_index = 0;
	ImVec2 cursor_pos = { 0, 250 };	// make this dynamics later to set the cursor position once and forever

	std::map<std::string, std::string> help_table {
		{ "W",			 "move Forward" },
		{ "S",			 "move Backward" },
		{ "A",			 "move Left" },
		{ "D",			 "move Right" },
		{ "SPACE",		 "move Up" },
		{ "CTRL",		 "move Down" },
		{ "SHIFT(hold)", "move faster" },
		{ "C",			 "enable/disable 'Creative' mode" },
		{ "E",			 "enable/disable object selection" },
		{ "R",			 "select pointed object for manipulation" },
		{ "ARROW UP",	 "move Forward the selected object" },
		{ "ARROW DOWN",	 "move Backward the selected object" },
		{ "ENTER",		 "place selected object" },
		{ "L",			 "switch ON 'Strips' mode" },
		{ "F",			 "switch OFF 'Strips' mode" },
		{ "ESC",		 "quit" }
	};
};
