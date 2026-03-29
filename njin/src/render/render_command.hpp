#pragma once

#include "renderer_defines.hpp"
#include "resource_descriptions.hpp"

#include <glm/glm.hpp>

namespace njin::rend
{

struct BufferInfo
{
    BufferID id;
    uint32_t offset = 0;
    uint32_t count = 0;
};

struct DrawCommand
{
    BufferInfo vertex_buffer_info;
    BufferInfo index_buffer_info;
    PipelineID pipeline;
    glm::mat4 model_matrix{1.0f};
    TextureID texture{};
};

struct FrameData
{
    glm::mat4 view{1.0f};
    glm::mat4 projection{1.0f};
};

}; // namespace njin::rend