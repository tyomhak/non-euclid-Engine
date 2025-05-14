#pragma once

#include "layer.hpp"
#include "window.hpp"

namespace njin
{

class UILayer : public Layer
{
public:
    UILayer(Window* window);
    ~UILayer();

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate() override;
    void OnEvent(Event& e) override;

protected:
    void Init(Window* window);
    
private:
    Window* _parent_window{nullptr};
    void* _context{nullptr};
};


}