#include "application.hpp"

#include "window.hpp"
#include "window_event.hpp"
#include "layer.hpp"
#include "input.hpp"
#include "key_codes.hpp"

#include "render/renderer.hpp"

#include "duration.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdint>
#include <array>

namespace njin
{

Application::Application()
{
    _main_window = std::unique_ptr<Window>(Window::Create());
    _main_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

    // --- Renderer ---
    _renderer = std::make_unique<rend::Renderer>(rend::RendererAPI::OpenGL);

    // --- Demo shader (MVP + texture) ---
    rend::ShaderDesc shader_desc;
    shader_desc.vert_src = R"glsl(
        #version 450 core

        layout(location = 0) in vec3 aPosition;
        layout(location = 1) in vec2 aTexCoord;

        uniform mat4 u_Model;
        uniform mat4 u_View;
        uniform mat4 u_Projection;

        out vec2 vTexCoord;

        void main()
        {
            gl_Position = u_Projection * u_View * u_Model * vec4(aPosition, 1.0);
            vTexCoord = aTexCoord;
        }
    )glsl";

    shader_desc.frag_src = R"glsl(
        #version 450 core

        in vec2 vTexCoord;

        uniform sampler2D u_Texture;

        out vec4 FragColor;

        void main()
        {
            FragColor = texture(u_Texture, vTexCoord);
        }
    )glsl";

    _demo_shader = _renderer->create_shader(shader_desc);

    // --- Cube geometry (position vec3 + texcoord vec2 per vertex) ---
    // clang-format off
    const std::array<float, 120> cube_verts = {
        // Front face (z = +0.5)
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        // Back face (z = -0.5)
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        // Top face (y = +0.5)
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        // Bottom face (y = -0.5)
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
        // Right face (x = +0.5)
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        // Left face (x = -0.5)
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    };

    const std::array<uint32_t, 36> cube_indices = {
         0,  1,  2,   2,  3,  0,  // front
         4,  5,  6,   6,  7,  4,  // back
         8,  9, 10,  10, 11,  8,  // top
        12, 13, 14,  14, 15, 12,  // bottom
        16, 17, 18,  18, 19, 16,  // right
        20, 21, 22,  22, 23, 20,  // left
    };
    // clang-format on

    rend::BufferDesc vbo_desc{};
    vbo_desc.size = static_cast<uint32_t>(cube_verts.size() * sizeof(float));
    vbo_desc.usage = rend::BufferUsage::Vertex;
    vbo_desc.data = const_cast<float*>(cube_verts.data());
    _demo_vbo = _renderer->create_buffer(vbo_desc);

    rend::BufferDesc ibo_desc{};
    ibo_desc.size = static_cast<uint32_t>(cube_indices.size() * sizeof(uint32_t));
    ibo_desc.usage = rend::BufferUsage::Index;
    ibo_desc.data = const_cast<uint32_t*>(cube_indices.data());
    _demo_ibo = _renderer->create_buffer(ibo_desc);

    // --- Pipeline (vertex layout + depth) ---
    rend::PipelineDesc pipeline_desc{};
    pipeline_desc.shader = _demo_shader;
    pipeline_desc.depthTest = true;
    pipeline_desc.depthWrite = true;
    pipeline_desc.vertex_layout.stride = 5 * sizeof(float); // pos(3) + uv(2)
    pipeline_desc.vertex_layout.attributes = {
        { 0, rend::VertexAttribType::Float3, 0 },                    // aPosition
        { 1, rend::VertexAttribType::Float2, 3 * sizeof(float) },    // aTexCoord
    };
    _demo_pipeline = _renderer->create_pipeline(pipeline_desc);

    // --- Procedural checker texture ---
    constexpr uint32_t tex_size = 64;
    std::array<uint8_t, tex_size * tex_size * 4> checker{};
    for (uint32_t y = 0; y < tex_size; y++)
    {
        for (uint32_t x = 0; x < tex_size; x++)
        {
            bool white = ((x / 8) + (y / 8)) % 2 == 0;
            uint8_t c = white ? 255 : 80;
            uint32_t i = (y * tex_size + x) * 4;
            checker[i + 0] = c;
            checker[i + 1] = c;
            checker[i + 2] = c;
            checker[i + 3] = 255;
        }
    }

    rend::TextureDesc tex_desc{};
    tex_desc.width = tex_size;
    tex_desc.height = tex_size;
    tex_desc.format = rend::Format::RGBA8;
    tex_desc.usage = rend::TextureUsage::Sampled;
    tex_desc.data = checker.data();
    _demo_texture = _renderer->create_texture(tex_desc);
}

Application* Application::Get()
{
    static Application app{};
    return &app;
}

Application::~Application()
{
    
}

void Application::Run()
{
    {
		// Necessary for capturing window size when the application starts.
        int width = _main_window->GetWidth();
        int height = _main_window->GetHeight();
        WindowResizeEvent onStartWindowResizeEvent(width, height);
        OnEvent(onStartWindowResizeEvent);
    }

    while (_is_running)
    {
        DurationLogger frameDuration("Time per Frame: ");
        _main_window->PollEvents();

        // --- Camera input (temporary — replaced by PlayerController in Phase 2) ---
        const float speed = 0.05f;
        const float look_speed = 1.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(_camera_yaw)) * cos(glm::radians(_camera_pitch));
        front.y = sin(glm::radians(_camera_pitch));
        front.z = sin(glm::radians(_camera_yaw)) * cos(glm::radians(_camera_pitch));
        front = glm::normalize(front);
        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

        if (Input::IsKeyPressed(KeyCode::Key_W)) _camera_pos += front * speed;
        if (Input::IsKeyPressed(KeyCode::Key_S)) _camera_pos -= front * speed;
        if (Input::IsKeyPressed(KeyCode::Key_A)) _camera_pos -= right * speed;
        if (Input::IsKeyPressed(KeyCode::Key_D)) _camera_pos += right * speed;
        if (Input::IsKeyPressed(KeyCode::Key_UP))    _camera_pitch += look_speed;
        if (Input::IsKeyPressed(KeyCode::Key_DOWN))  _camera_pitch -= look_speed;
        if (Input::IsKeyPressed(KeyCode::Key_LEFT))  _camera_yaw -= look_speed;
        if (Input::IsKeyPressed(KeyCode::Key_RIGHT)) _camera_yaw += look_speed;
        _camera_pitch = glm::clamp(_camera_pitch, -89.0f, 89.0f);

        // --- Frame data ---
        float aspect = static_cast<float>(_main_window->GetWidth())
                     / static_cast<float>(_main_window->GetHeight());
        rend::FrameData frame;
        frame.view = glm::lookAt(_camera_pos, _camera_pos + front, glm::vec3(0.0f, 1.0f, 0.0f));
        frame.projection = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);

        _renderer->begin_frame(frame);

        // --- Submit demo cube ---
        rend::DrawCommand cmd{};
        cmd.vertex_buffer_info.id = _demo_vbo;
        cmd.vertex_buffer_info.offset = 0;
        cmd.vertex_buffer_info.count = 24;
        cmd.index_buffer_info.id = _demo_ibo;
        cmd.index_buffer_info.offset = 0;
        cmd.index_buffer_info.count = 36;
        cmd.pipeline = _demo_pipeline;
        cmd.model_matrix = glm::mat4(1.0f);
        cmd.texture = _demo_texture;
        _renderer->submit(cmd);

        _renderer->end_frame();

        // --- Layers (UI) ---
        for (auto layerPtr : _layer_stack)
            layerPtr->OnUpdate();

        _main_window->Draw();
    }
}


void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event); 
    dispatcher.Dispatch<WindowCloseEvent>([this](Event& e){ return OnWindowClose(e); });
    dispatcher.Dispatch<WindowFocusEvent>([this](Event& e){ return OnWindowFocus(e); });
    dispatcher.Dispatch<WindowLostFocusEvent>([this](Event& e){ return OnWindowLostFocus(e); });
    dispatcher.Dispatch<WindowMovedEvent>([this](Event& e){ return OnWindowMoved(e); });

    _main_window->OnEvent(event);
    for(auto it = _layer_stack.end(); it != _layer_stack.begin();)
    {
        (*--it)->OnEvent(event);
        if (event.IsHandled())
            break;
    }
}


bool Application::OnWindowClose(Event& event)
{
    _is_running = false;
    return true;
}


}