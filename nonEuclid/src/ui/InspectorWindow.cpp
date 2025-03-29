#include "InspectorWindow.h"

using namespace ui;

InspectorWindow::InspectorWindow(Window* window, EventHandler* eventHandler)
    : UIWindow(window)
    , _eventHandler(eventHandler)
{
    ImGui::StyleColorsDark();
}

void InspectorWindow::DefineWindow()
{
    static const std::string window_name{"Inspector"};

    auto window_flags = ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_MenuBar;
    ImGui::SetNextWindowPos({0,0});
    ImGui::SetNextWindowSize({360.0f, (float)_parent_window->GetHeight()});
    ImGui::Begin(window_name.c_str(), &tabs_active, window_flags);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            ImGui::MenuItem("Console");
        }

        ImGui::EndMenuBar();
    }
    
    // ImGui::SameLine(ImGui::GetWindowWidth() - 60.0f); // adds next functionality on the same line with RightAline



    if (ImGui::Button(helper_window_active ? "Hide Input Map" : "Show Input Map")) { 
        helper_window_active = !helper_window_active;
    }
    if (helper_window_active)
    {
        // ImGui::SetNextWindowSize({320, 290});
        // if (ImGui::Begin("Helper: instructions", &helper_window_active, window_flags))
        
        auto child_flags = ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY;
        auto window_flags = ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoMove;
        if (ImGui::BeginChild("Helper: instructions", {360,320}, child_flags, window_flags))
        {            
            // ImGui::BeginChild("Scrolling");			// enable scrolling in the window

            auto table_flags = ImGuiTableFlags_Resizable 
                | ImGuiTableFlags_SizingFixedFit 
                | ImGuiTableFlags_RowBg 
                | ImGuiTableFlags_BordersOuter 
                | ImGuiTableFlags_BordersInner;
            if (ImGui::BeginTable("Input", 2, table_flags))
            {
                for (const auto& [key, description] : help_table)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(key.c_str());
                    
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text(description.c_str());
                }
                ImGui::EndTable();
            }
            // ImGui::EndChild();
        }
        ImGui::EndChild();
    }

    ImGui::SeparatorText("Level Editor");

    // choosing object to be created
    ImGui::Combo("Choose object", &selected_object_item, objects_menu_items, IM_ARRAYSIZE(objects_menu_items));
    
    ImGui::Dummy(ImVec2(0.0f, 7.0f));

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

    // ImGui::SetCursorPos(cursor_pos);	// places upcoming attributes of the window on the place that is set by cursor

    // Selected object status display
    ImGui::Text((" Update object ID: " + _eventHandler->updateObjectId).c_str());
    ImGui::Text(("Under View object ID: " + _eventHandler->underViewObjectId).c_str());


    // Save, Delete, Create functionality
    ImGui::Separator();
    ImGui::Spacing();ImGui::Spacing();	// can be replaced by ImGui::Dummy(ImVec2(0.0f, 2.0f));
    if (ImGui::Button("Delete"))
    {
        _eventHandler->DeleteObject();
    }

    ImGui::SameLine(ImGui::GetWindowWidth() - 130.0f);
    if (ImGui::Button("Create"))
    {
        if (objects_menu_items[selected_object_item] != "" && objects_menu_items[selected_object_item] != "portal")
        {
            _eventHandler->creativeEnabled = true;
            glm::vec3 position = glm::vec3(-0.5f, 0.0f, 0.0f);
            _eventHandler->updateObjectId = _eventHandler->AddObject(objects_menu_items[selected_object_item], position);	// add also the 'size' and 'color'
        }

        if (objects_menu_items[selected_object_item] == "portal")
        {
            Portal::portalBackground[0] = 0.3f;
            Portal::portalBackground[1] = 0.8f;
            Portal::portalBackground[2] = 1.0f;
            _eventHandler->AddPortals();
        }
    }

    ImGui::SameLine(ImGui::GetWindowWidth() - 60.0f);
    if (ImGui::Button("Save"))
    {
        _eventHandler->creativeEnabled = false;
        _eventHandler->underViewObjectId = "None";
        _eventHandler->updateObjectId = "None";
    }

    ImGui::End();
}