#pragma once


#include <map>
#include <vector>

#include "UIWindow.h"

class Engine;

namespace ui
{

class InspectorWindow : public UIWindow
{
public:
    InspectorWindow(Engine* engine, Window* window, EventHandler* eventHandler);

protected:
    void DefineWindow() override;

private:
    void SaveScene();
    void LoadScene();

private:
    Engine* _engine = nullptr;
	EventHandler* _eventHandler = nullptr;

    const char* objects_menu_items[4]{ "", "cube", "backpack", "portal" };
	int selected_object_item = 0;
	
    bool helper_window_active = false;

	short tabs_index = 0;

	ImVec2 cursor_pos = { 0, 250 };

    const std::map<std::string, std::string> help_table {
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






}