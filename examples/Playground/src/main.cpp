
#include "application.hpp"
#include "ui/ui_layer.hpp"
#include "duration.hpp"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include "input.hpp"

#include "event.hpp"
#include "key_event.hpp"

#include <deque>



class ProfilerUI : public njin::UILayer
{
public:
    using njin::UILayer::UILayer;

    void OnUpdate() override
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        if (ImGui::IsKeyPressed(ImGuiKey_Tab, false))
            _is_open = !_is_open;

        if (_is_open)
        {
            static const std::string window_name{"Profiling"};
            auto window_flags = ImGuiWindowFlags_NoResize
                    | ImGuiWindowFlags_NoMove
                    | ImGuiWindowFlags_MenuBar;
            ImGui::SetNextWindowPos({0,0});
            ImGui::SetNextWindowSize({375.0f, 375.0f * 2.f});
            ImGui::Begin(window_name.c_str(), nullptr, window_flags);


            auto curr_frame_time = _frame_timer.get_ms();
            _frame_times.push_back(curr_frame_time);
            _frame_time_sum += curr_frame_time;
            if (_frame_times.size() > _frame_count)
            {
                _frame_time_sum -= _frame_times.front();
                _frame_times.pop_front();
            }

            std::string frameDurationTxt = "AVG Frame Duration: " + std::to_string(_frame_time_sum / _frame_times.size());
            _frame_timer.reset();
            ImGui::Text(frameDurationTxt.c_str());

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }  

private:
    njin::Timer _frame_timer{};
    long long _frame_time_sum{0};
    std::deque<long long> _frame_times{};
    unsigned _frame_count{60u};

    bool _is_open{false};
};

int main()
{
    auto appPtr = njin::Application::Get();

    appPtr->AttachOverlay(new ProfilerUI(appPtr->GetMainWindow()));
    appPtr->Run();
}