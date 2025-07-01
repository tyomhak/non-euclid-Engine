#pragma once

namespace njin::render
{
    class RenderContext
    {
    public:
        virtual ~RenderContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
        virtual void Clear() = 0;
    };

};