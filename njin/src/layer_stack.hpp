#pragma once

#include <vector>

namespace njin
{

class Layer;

class LayerStack
{
public:
    using layer_vec = std::vector<Layer*>;
    using layer_vec_it = layer_vec::iterator;

    LayerStack();
    ~LayerStack();

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* overlay);

    layer_vec_it begin() { return _layers.begin(); }
    layer_vec_it end() { return _layers.end(); }

protected:

private:
    layer_vec _layers{};
    layer_vec_it _layers_insert_it{};
};

}