#include "Playground.hpp"

#include "ui_layer.hpp"

using namespace njin;

Playground::Playground() 
    : Application()
{
    AttachLayer(new UILayer(GetMainWindow()));
}
