#include "Playground.hpp"

#include "ui/ui_layer.hpp"

using namespace njin;

Playground::Playground() 
    : Application()
{
    AttachLayer(new UILayer(GetMainWindow()));
}
