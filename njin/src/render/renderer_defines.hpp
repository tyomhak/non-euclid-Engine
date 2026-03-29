#pragma once

#include <cstdint>

#include "id.hpp"


namespace njin::rend 
{



enum class RendererAPI
{
    None = 0,
    OpenGL = 1,
    DirectX = 2,
    Vulkan = 3,
    Metal = 4
};


struct BufferTag{};
using BufferID = ID<BufferTag>;

struct TextureTag{};
using TextureID = ID<TextureTag>;

struct ShaderTag{};
using ShaderID = ID<ShaderTag>;

struct PipelineTag{};
using PipelineID = ID<PipelineTag>;


enum class BufferUsage
{
    Vertex,
    Index,
    Uniform
};

enum class Format
{
    RGBA8,
    RGBA16F,
    Depth24Stencil8
};

enum class TextureUsage
{
    Sampled,
    ColorAttachment,
    DepthStencil
};




} // namespace njin::rend

