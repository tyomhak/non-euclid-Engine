#pragma once

#include "render_backend.hpp"

#include <vector>

#include <glad/gl.h>

namespace njin::rend
{

struct GLPipeline
{
    GLuint vao{0};
    ShaderID shader{};
    uint32_t stride{0};
    bool depthTest{true};
    bool depthWrite{true};
};

class GLRendererBackend : public RendererBackend
{
public:
    bool init() override;
    void shutdown() override;

    BufferID create_buffer(const BufferDesc& desc) override;
    ShaderID create_shader(const ShaderDesc& desc) override;
    PipelineID create_pipeline(const PipelineDesc& desc) override;
    TextureID create_texture(const TextureDesc& desc) override;

    void begin_frame(const FrameData& frame_data) override;
    void end_frame() override;
    void execute(const std::vector<DrawCommand>& cmds) override;

private:
    GLuint create_shader(const std::string& src, GLenum shader_type);
    GLuint create_program(GLuint vertShader, GLuint fragShader);

private:
    std::vector<GLuint> _textures{};
    std::vector<GLuint> _buffers{};
    std::vector<GLuint> _programs{};
    std::vector<GLPipeline> _pipelines{};
    FrameData _current_frame{};
};


} // namespace njin::rend