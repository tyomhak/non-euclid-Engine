#pragma once

#include <string>
#include <vector>

#include "renderer_defines.hpp"

namespace njin::rend
{

struct BufferDesc
{
    uint32_t size;
    BufferUsage usage;
    void* data = nullptr;
};

struct ShaderDesc
{
    std::string vert_src;
    std::string frag_src;
};

enum class VertexAttribType
{
    Float,
    Float2,
    Float3,
    Float4
};

struct VertexAttribute
{
    uint32_t location;
    VertexAttribType type;
    uint32_t offset;
};

struct VertexLayout
{
    std::vector<VertexAttribute> attributes;
    uint32_t stride = 0;
};

struct PipelineDesc
{
    ShaderID shader;
    VertexLayout vertex_layout;
    bool depthTest = true;
    bool depthWrite = true;
};

struct TextureDesc
{
    uint32_t width;
    uint32_t height;
    Format format;
    TextureUsage usage;
    void* data = nullptr;
};

}