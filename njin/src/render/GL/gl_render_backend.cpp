#include "gl_render_backend.hpp"

#include "logging.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace njin::rend
{

namespace conversions
{
GLuint gl_format(Format format)
{
    switch (format)
    {
        case Format::RGBA8: return GL_RGBA8;
        case Format::RGBA16F: return GL_RGBA16F;
        case Format::Depth24Stencil8: return GL_DEPTH24_STENCIL8;
        default: return 0;
    }
}

GLuint gl_format_type(Format format)
{
    switch (format)
    {
        case Format::RGBA8: return GL_UNSIGNED_BYTE;
        case Format::RGBA16F: return GL_HALF_FLOAT;
        case Format::Depth24Stencil8: return GL_UNSIGNED_INT_24_8;
        default: return 0;
    }
}

GLuint gl_format_base(Format format)
{
    switch (format)
    {
        case Format::RGBA8:
        case Format::RGBA16F:
            return GL_RGBA;
        case Format::Depth24Stencil8:
            return GL_DEPTH_STENCIL;
        default: return 0;
    }
}

};

namespace
{

GLint attrib_component_count(VertexAttribType type)
{
    switch (type)
    {
        case VertexAttribType::Float:  return 1;
        case VertexAttribType::Float2: return 2;
        case VertexAttribType::Float3: return 3;
        case VertexAttribType::Float4: return 4;
        default: return 0;
    }
}

} // anonymous namespace

std::unique_ptr<RendererBackend> create_render_backend(RendererAPI api)
{
    switch (api)
    {
        case RendererAPI::OpenGL:
            return std::make_unique<GLRendererBackend>();
        default:
            throw std::runtime_error("Unsupported Renderer API");
    }
}
} // namespace njin::rend

namespace njin::rend
{

bool GLRendererBackend::init()
{
    return true;
}

void GLRendererBackend::shutdown()
{
    for (const auto& pipeline : _pipelines)
    {
        if (pipeline.vao)
            glDeleteVertexArrays(1, &pipeline.vao);
    }
    _pipelines.clear();

    for (GLuint buffer : _buffers)
    {
        glDeleteBuffers(1, &buffer);
    }
    _buffers.clear();

    for (GLuint texture : _textures)
    {
        glDeleteTextures(1, &texture);
    }
    _textures.clear();

    for (GLuint program : _programs)
    {
        glDeleteProgram(program);
    }
    _programs.clear();
}

BufferID GLRendererBackend::create_buffer(const BufferDesc& desc)
{
    GLuint buffer;
    glGenBuffers(1, &buffer);

    GLenum target = desc.usage == BufferUsage::Vertex ? GL_ARRAY_BUFFER :
                    desc.usage == BufferUsage::Index ? GL_ELEMENT_ARRAY_BUFFER :
                    desc.usage == BufferUsage::Uniform ? GL_UNIFORM_BUFFER : 0;

    glBindBuffer(target, buffer);
    glBufferData(target, desc.size, desc.data, GL_STATIC_DRAW);
    _buffers.push_back(buffer);

    return BufferID(static_cast<uint32_t>(_buffers.size() - 1));
}

ShaderID GLRendererBackend::create_shader(const ShaderDesc& desc)
{
    auto vertShader = create_shader(desc.vert_src, GL_VERTEX_SHADER);
    auto fragShader = create_shader(desc.frag_src, GL_FRAGMENT_SHADER);

    if (!vertShader || !fragShader)
        return ShaderID::Invalid();

    auto program = create_program(vertShader, fragShader);
    if (!program)
        return ShaderID::Invalid();

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    _programs.push_back(program);
    return ShaderID(static_cast<uint32_t>(_programs.size() - 1));
}

PipelineID GLRendererBackend::create_pipeline(const PipelineDesc& desc)
{
    if (!desc.shader)
        return PipelineID::Invalid();

    GLPipeline pipeline{};
    pipeline.shader = desc.shader;
    pipeline.depthTest = desc.depthTest;
    pipeline.depthWrite = desc.depthWrite;
    pipeline.stride = desc.vertex_layout.stride;

    glCreateVertexArrays(1, &pipeline.vao);

    for (const auto& attr : desc.vertex_layout.attributes)
    {
        glEnableVertexArrayAttrib(pipeline.vao, attr.location);
        glVertexArrayAttribFormat(pipeline.vao, attr.location,
                                  attrib_component_count(attr.type),
                                  GL_FLOAT, GL_FALSE, attr.offset);
        glVertexArrayAttribBinding(pipeline.vao, attr.location, 0);
    }

    _pipelines.push_back(pipeline);
    return PipelineID(static_cast<uint32_t>(_pipelines.size() - 1));
}

TextureID GLRendererBackend::create_texture(const TextureDesc& desc)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLenum internalFormat = conversions::gl_format(desc.format);
    GLenum format = conversions::gl_format_base(desc.format);
    GLenum type = conversions::gl_format_type(desc.format);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, desc.width, desc.height, 0, format, type, desc.data);

    // Set default filtering and wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    _textures.push_back(texture);
    return TextureID(static_cast<uint32_t>(_textures.size() - 1));
}

void GLRendererBackend::begin_frame(const FrameData& frame_data)
{
    _current_frame = frame_data;
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRendererBackend::end_frame()
{
}

void GLRendererBackend::execute(const std::vector<DrawCommand>& commands)
{
    for (const auto& cmd : commands)
    {
        const auto& pipeline = _pipelines[cmd.pipeline.to_raw()];
        GLuint program = _programs[pipeline.shader.to_raw()];

        // Bind pipeline state
        glBindVertexArray(pipeline.vao);
        glUseProgram(program);

        // Depth state
        if (pipeline.depthTest)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthMask(pipeline.depthWrite ? GL_TRUE : GL_FALSE);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }

        // Bind vertex buffer to VAO binding point 0
        GLuint vbo = _buffers[cmd.vertex_buffer_info.id.to_raw()];
        glVertexArrayVertexBuffer(pipeline.vao, 0, vbo,
                                  cmd.vertex_buffer_info.offset,
                                  pipeline.stride);

        // Bind index buffer
        GLuint ibo = _buffers[cmd.index_buffer_info.id.to_raw()];
        glVertexArrayElementBuffer(pipeline.vao, ibo);

        // Set per-frame uniforms (view, projection)
        GLint viewLoc = glGetUniformLocation(program, "u_View");
        GLint projLoc = glGetUniformLocation(program, "u_Projection");
        if (viewLoc >= 0)
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_current_frame.view));
        if (projLoc >= 0)
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_current_frame.projection));

        // Set per-draw uniforms (model matrix)
        GLint modelLoc = glGetUniformLocation(program, "u_Model");
        if (modelLoc >= 0)
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cmd.model_matrix));

        // Bind texture
        if (cmd.texture.is_valid())
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _textures[cmd.texture.to_raw()]);
            GLint texLoc = glGetUniformLocation(program, "u_Texture");
            if (texLoc >= 0)
                glUniform1i(texLoc, 0);
        }

        // Draw
        glDrawElements(GL_TRIANGLES,
                       cmd.index_buffer_info.count,
                       GL_UNSIGNED_INT,
                       reinterpret_cast<void*>(static_cast<uintptr_t>(cmd.index_buffer_info.offset)));
    }
}



GLuint GLRendererBackend::create_shader(const std::string& src, GLenum shader_type)
{
    auto shader = glCreateShader(shader_type);
    auto c_src = static_cast<const GLchar*>(src.c_str());

    glShaderSource(shader, 1, &c_src, nullptr);
    glCompileShader(shader);

    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE)
    {
        GLint logLength{0};
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength)
        {
            std::vector<GLchar> infoLog(logLength);
            glGetShaderInfoLog(shader, logLength, &logLength, &infoLog[0]);
            njin::Logger::Error("Failed to compile GL shader: {}", infoLog.data());
        }
        else
            njin::Logger::Error("Failed to compile GL shader: No error log available");
        
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}
GLuint GLRendererBackend::create_program(GLuint vertShader, GLuint fragShader)
{
    if (!vertShader || !fragShader)
        return 0;
    
    auto program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result != GL_TRUE)
    {
        GLsizei infoSize;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoSize);
        if (infoSize)
        {
            std::vector<GLchar> log(infoSize);
            glGetProgramInfoLog(program, infoSize, &infoSize, &log[0]);
            njin::Logger::Error("Failed Linking GL Program with error: {}\n", log.data());
        }
        else
            njin::Logger::Error("Failed Linking GL Program with error: No error log available.\n");

        glDetachShader(program, fragShader);
        glDetachShader(program, vertShader);
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

}; // namespace njin::rend