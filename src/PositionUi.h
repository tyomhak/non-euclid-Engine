#pragma once

#include "UiWindow.h"
#include "IncludeHeaders.h"
#include <string>

class PositionUi: protected UiWindow
{
public:
	PositionUi(std::string _name, EventHandler* _eventHandler) :
		UiWindow(_name, _eventHandler)
	{
		my_tool_active = true;
	}

	// void Render()
	// {
	// 	static float position[] = { 0.0f, 0.0f, 0.0f };

	// 	//ImGui::Checkbox()

	// 	// stuff to be displayed in tab 1
	// 	ImGui::Begin("Object Position window", &my_tool_active, ImGuiWindowFlags_MenuBar);

	// 	ImGui::SliderFloat3("position", position, -5.0f, 5.0f);	// translation buttons (sliders)

	// 	ImGui::End();


	// 	eventHandler->moveSelectedObjectToPosition(glm::vec3(position[0], position[1], position[2]));

	// }

private:
	bool my_tool_active;	// To Be Deleted
};
