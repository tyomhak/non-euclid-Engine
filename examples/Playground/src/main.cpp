
#include "application.hpp"
#include "ui/ui_layer.hpp"

int main()
{
    auto appPtr = njin::Application::Get();

    appPtr->AttachOverlay(new njin::UILayer(appPtr->GetMainWindow()));
    appPtr->Run();
}