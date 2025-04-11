#include "InspectorWindow.h"

#include "Engine.h"

using namespace ui;

InspectorWindow::InspectorWindow(Engine* engine, Window* window, EventHandler* eventHandler)
    : UIWindow(window)
    , _engine(engine)
    , _eventHandler(eventHandler)
{
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 3.0f;
    style.FrameRounding = 3.0f;
    style.ScrollbarRounding = 3.0f;



    style.Colors[ImGuiCol_Text]                  = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
    style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_ChildBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
    style.Colors[ImGuiCol_Border]                = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
    style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
    style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
    style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
    // style.Colors[ImGuiCol_ComboBg]               = ImVec4(0.1f, 0.1f, 0.1f, 0.99f);
    style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
    style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
    style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
    style.Colors[ImGuiCol_Button]                = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
    style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
    style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_Header]                = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
    style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    // style.Colors[ImGuiCol_CloseButton]           = ImVec4(0.50f, 0.50f, 0.90f, 0.50f);
    // style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.70f, 0.70f, 0.90f, 0.60f);
    // style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    // style.Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void InspectorWindow::DefineWindow()
{
    static const std::string window_name{"Inspector"};

    auto window_flags = ImGuiWindowFlags_NoResize
            // | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_MenuBar;
    ImGui::SetNextWindowPos({0,0});
    ImGui::SetNextWindowSize({375.0f, (float)_parent_window->GetHeight()});
    ImGui::Begin(window_name.c_str(), nullptr, window_flags);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Scene"))
        {
            bool save_scene = false;
            ImGui::MenuItem("Save", nullptr, &save_scene);
            if (save_scene)
                SaveScene();

            bool load_scene = false;
            ImGui::MenuItem("Load", nullptr, &load_scene);
            if (load_scene)
                LoadScene();

            ImGui::EndMenu();
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

void InspectorWindow::SaveScene()
{
    if (_engine)
        _engine->SaveWorld();
}

void InspectorWindow::LoadScene()
{
    std::cout << "Loading Scene (Not implemented yet)\n";
}