#pragma once

#include "platform/OpenGL/Render/GLShader.hpp"

namespace njin
{

class Renderer
{
public:
    [[nodiscard]] static Shader* create_shader(const std::string& vert_src, const std::string& frag_src)
    {
        return new GLShader(vert_src, frag_src);
    }

private:

};

};