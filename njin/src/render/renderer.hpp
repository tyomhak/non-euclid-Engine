#pragma once

#include "renderer_defines.hpp"
#include "resource_descriptions.hpp"

#include "render_backend.hpp"


namespace njin::rend
{

std::unique_ptr<RendererBackend> create_render_backend(RendererAPI api);

class Renderer
{
public:
    Renderer(RendererAPI api)
        : _backend(std::move(create_render_backend(api)))
    {
        _backend->init();
    }

    ~Renderer()
    {
        _backend->shutdown();
    }

    TextureID create_texture(const TextureDesc& desc)
    {
        return _backend->create_texture(desc);
    }

    BufferID create_buffer(const BufferDesc& desc)
    {
        return _backend->create_buffer(desc);
    }

    ShaderID create_shader(const ShaderDesc& desc)
    {
        return _backend->create_shader(desc);
    }

    PipelineID create_pipeline(const PipelineDesc& desc)
    {
        return _backend->create_pipeline(desc);
    }

    void begin_frame(const FrameData& frame_data)
    {
        _commands.clear();
        _backend->begin_frame(frame_data);
    }

    void submit(const DrawCommand& cmd)
    {
        _commands.push_back(cmd);
    }

    void end_frame()
    {
        _backend->execute(_commands);
        _backend->end_frame();
    }

private:
    std::unique_ptr<RendererBackend> _backend;
    std::vector<DrawCommand> _commands;
};

};