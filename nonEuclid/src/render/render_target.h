#pragma once

namespace render
{


class RenderTarget
{
public:
    virtual ~RenderTarget(){}

    virtual void SetActive() = 0;
    virtual void Update() = 0;

private:

};

class WindowRenderTarget : public RenderTarget
{
public:
    void SetActive() override
    {

    }

    void Update() override
    {
        // swap buffers
    }
};

class TextureRenderTarget : public RenderTarget
{
public:

};

}