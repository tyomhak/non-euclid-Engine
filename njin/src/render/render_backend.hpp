#pragma once

#include "renderer_defines.hpp"
#include "resource_descriptions.hpp"
#include "render_command.hpp"


namespace njin::rend
{

class RendererBackend
{
public:
    virtual ~RendererBackend() = default;

    virtual bool init() = 0;
    virtual void shutdown() = 0;

    virtual BufferID create_buffer(const BufferDesc& desc) = 0;
    virtual ShaderID create_shader(const ShaderDesc& desc) = 0;
    virtual PipelineID create_pipeline(const PipelineDesc& desc) = 0;
    virtual TextureID create_texture(const TextureDesc& desc) = 0;

    virtual void begin_frame(const FrameData& frame_data) = 0;
    virtual void end_frame() = 0;
    virtual void execute(const std::vector<DrawCommand>& cmds) = 0;
};

}; // namespace njin::rend