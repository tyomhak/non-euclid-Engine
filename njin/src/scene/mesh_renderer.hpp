#pragma once

#include "component.hpp"
#include "render/render_command.hpp"
#include "render/renderer_defines.hpp"

namespace njin
{

// Holds renderer resource handles needed to draw one mesh.
// Populated by asset loading code; emits a DrawCommand each frame.
struct MeshRenderer : public Component
{
    rend::BufferID  vbo{};
    rend::BufferID  ibo{};
    rend::PipelineID pipeline{};
    rend::TextureID  texture{};
    uint32_t index_count{0};
};

} // namespace njin
