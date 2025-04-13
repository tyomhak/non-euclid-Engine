#include "layer_stack.hpp"

#include "layer.hpp"

namespace njin
{

LayerStack::LayerStack()
    : _layers_insert_it(begin())
{}
LayerStack::~LayerStack()
{
    for (auto layer : _layers)
        delete layer;
}

void LayerStack::PushLayer(Layer* layer)
{
    _layers_insert_it = _layers.emplace(_layers_insert_it, layer);
}
void LayerStack::PushOverlay(Layer* overlay)
{
    _layers.emplace_back(overlay);
}
void LayerStack::PopLayer(Layer* layer)
{
    if (auto it = std::find(_layers.begin(), _layers.end(), layer); it != _layers.end())
    {
        _layers.erase(it);
        _layers_insert_it--;
    }

}
void LayerStack::PopOverlay(Layer* overlay)
{
    auto it = std::find(_layers.begin(), _layers.end(), overlay);
    if (it != _layers.end())
        _layers.erase(it);
}


}