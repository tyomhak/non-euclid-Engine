#pragma once

#include "render/renderer.hpp"
#include "render/resource_descriptions.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

namespace njin
{

class ShaderLoader
{
public:
    /// Load a vertex + fragment shader pair from disk and create a GPU shader.
    /// @param vert_path  Path to the .vert file.
    /// @param frag_path  Path to the .frag file.
    static rend::ShaderID load(rend::Renderer& renderer,
                               const std::string& vert_path,
                               const std::string& frag_path)
    {
        rend::ShaderDesc desc;
        desc.vert_src = read_file(vert_path);
        desc.frag_src = read_file(frag_path);
        return renderer.create_shader(desc);
    }

private:
    static std::string read_file(const std::string& path)
    {
        std::ifstream file(path, std::ios::in);
        if (!file.is_open())
            throw std::runtime_error("ShaderLoader: cannot open '" + path + "'");

        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
};

} // namespace njin
