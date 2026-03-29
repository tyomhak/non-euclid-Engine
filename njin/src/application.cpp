#include "application.hpp"

#include "window.hpp"
#include "window_event.hpp"
#include "layer.hpp"
#include "input.hpp"
#include "key_codes.hpp"

#include "render/renderer.hpp"
#include "scene/scene.hpp"
#include "scene/camera.hpp"
#include "scene/mesh_renderer.hpp"

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

    _renderer = std::make_unique<rend::Renderer>(rend::RendererAPI::OpenGL);

    BuildDemoScene();

    _last_frame_time = std::chrono::steady_clock::now();
}

void Application::BuildDemoScene()
{
    // --- Shared shader ---
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

    auto shader = _renderer->create_shader(shader_desc);

    // --- Cube geometry ---
    // clang-format off
    const std::array<float, 120> cube_verts = {
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    };

    const std::array<uint32_t, 36> cube_indices = {
         0,  1,  2,   2,  3,  0,
         4,  5,  6,   6,  7,  4,
         8,  9, 10,  10, 11,  8,
        12, 13, 14,  14, 15, 12,
        16, 17, 18,  18, 19, 16,
        20, 21, 22,  22, 23, 20,
    };
    // clang-format on

    rend::BufferDesc vbo_desc{};
    vbo_desc.size = static_cast<uint32_t>(cube_verts.size() * sizeof(float));
    vbo_desc.usage = rend::BufferUsage::Vertex;
    vbo_desc.data = const_cast<float*>(cube_verts.data());
    auto vbo = _renderer->create_buffer(vbo_desc);

    rend::BufferDesc ibo_desc{};
    ibo_desc.size = static_cast<uint32_t>(cube_indices.size() * sizeof(uint32_t));
    ibo_desc.usage = rend::BufferUsage::Index;
    ibo_desc.data = const_cast<uint32_t*>(cube_indices.data());
    auto ibo = _renderer->create_buffer(ibo_desc);

    rend::PipelineDesc pipeline_desc{};
    pipeline_desc.shader = shader;
    pipeline_desc.depthTest = true;
    pipeline_desc.depthWrite = true;
    pipeline_desc.vertex_layout.stride = 5 * sizeof(float);
    pipeline_desc.vertex_layout.attributes = {
        { 0, rend::VertexAttribType::Float3, 0 },
        { 1, rend::VertexAttribType::Float2, 3 * sizeof(float) },
    };
    auto pipeline = _renderer->create_pipeline(pipeline_desc);

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
    auto texture = _renderer->create_texture(tex_desc);

    // --- Entities ---

    // Camera entity
    auto& cam_entity = _scene.spawn("Camera");
    cam_entity.transform.position = glm::vec3(0.0f, 0.0f, 3.0f);
    cam_entity.add_component<Camera>();
    _scene.set_active_camera(&cam_entity);

    // Cube entity
    auto& cube = _scene.spawn("Cube");
    auto& mr = cube.add_component<MeshRenderer>();
    mr.vbo = vbo;
    mr.ibo = ibo;
    mr.pipeline = pipeline;
    mr.texture = texture;
    mr.index_count = static_cast<uint32_t>(cube_indices.size());

    // Second cube offset to the side
    auto& cube2 = _scene.spawn("Cube2");
    cube2.transform.position = glm::vec3(2.0f, 0.0f, 0.0f);
    cube2.transform.rotation = glm::vec3(0.0f, 45.0f, 0.0f);
    auto& mr2 = cube2.add_component<MeshRenderer>();
    mr2.vbo = vbo;
    mr2.ibo = ibo;
    mr2.pipeline = pipeline;
    mr2.texture = texture;
    mr2.index_count = static_cast<uint32_t>(cube_indices.size());
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
        int width = _main_window->GetWidth();
        int height = _main_window->GetHeight();
        WindowResizeEvent onStartWindowResizeEvent(width, height);
        OnEvent(onStartWindowResizeEvent);
    }

    while (_is_running)
    {
        // --- Delta time ---
        auto now = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(now - _last_frame_time).count();
        _last_frame_time = now;

        // Cap dt to avoid spiral of death after breakpoints / alt-tab.
        if (dt > 0.25f)
            dt = 0.25f;

        _main_window->PollEvents();

        // --- Fixed timestep update ---
        _accumulator += dt;
        while (_accumulator >= FIXED_DT)
        {
            _scene.update(FIXED_DT);
            _accumulator -= FIXED_DT;
        }

        // --- Camera input (temporary — replaced by PlayerController in Phase 5) ---
        auto* cam_entity = _scene.active_camera();
        if (cam_entity)
        {
            auto* cam = cam_entity->get_component<Camera>();
            if (cam)
            {
                const float speed = 3.0f * dt;
                const float look_speed = 90.0f * dt;

                auto front = cam->front();
                auto right = cam->right();

                if (Input::IsKeyPressed(KeyCode::Key_W)) cam_entity->transform.position += front * speed;
                if (Input::IsKeyPressed(KeyCode::Key_S)) cam_entity->transform.position -= front * speed;
                if (Input::IsKeyPressed(KeyCode::Key_A)) cam_entity->transform.position -= right * speed;
                if (Input::IsKeyPressed(KeyCode::Key_D)) cam_entity->transform.position += right * speed;
                if (Input::IsKeyPressed(KeyCode::Key_UP))    cam->pitch += look_speed;
                if (Input::IsKeyPressed(KeyCode::Key_DOWN))  cam->pitch -= look_speed;
                if (Input::IsKeyPressed(KeyCode::Key_LEFT))  cam->yaw -= look_speed;
                if (Input::IsKeyPressed(KeyCode::Key_RIGHT)) cam->yaw += look_speed;
                cam->pitch = glm::clamp(cam->pitch, -89.0f, 89.0f);
            }
        }

        // --- Render ---
        float aspect = static_cast<float>(_main_window->GetWidth())
                     / static_cast<float>(_main_window->GetHeight());
        _scene.render(*_renderer, aspect);

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