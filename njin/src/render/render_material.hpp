#pragma once

#include "shader.hpp"

namespace njin
{
    struct RenderMaterial
    {
        virtual ~RenderMaterial() = default;
        // ShaderProgram shaderProgram;
    };
}