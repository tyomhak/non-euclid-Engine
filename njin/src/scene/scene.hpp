#pragma once

#include "entity.hpp"
#include "mesh_renderer.hpp"
#include "camera.hpp"
#include "render/renderer.hpp"

#include <vector>
#include <memory>
#include <string>

namespace njin
{

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    // Non-copyable, movable.
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    Scene(Scene&&) noexcept = default;
    Scene& operator=(Scene&&) noexcept = default;

    // --- Entity management ---

    Entity& spawn(std::string name = "Entity")
    {
        _entities.push_back(std::make_unique<Entity>(std::move(name)));
        return *_entities.back();
    }

    void destroy(const Entity& entity)
    {
        _entities.erase(
            std::remove_if(_entities.begin(), _entities.end(),
                [&entity](const auto& ptr) { return ptr.get() == &entity; }),
            _entities.end());
    }

    Entity* find(const std::string& name) const
    {
        for (const auto& e : _entities)
            if (e->name() == name)
                return e.get();
        return nullptr;
    }

    // --- Active camera ---

    void set_active_camera(Entity* camera_entity) { _active_camera = camera_entity; }
    Entity* active_camera() const { return _active_camera; }

    // --- Per-frame calls ---

    void update(float dt)
    {
        for (auto& entity : _entities)
            if (entity->is_active())
                entity->update(dt);
    }

    void render(rend::Renderer& renderer, float aspect_ratio)
    {
        // Build FrameData from active camera.
        rend::FrameData frame{};
        if (_active_camera)
        {
            auto* cam = _active_camera->get_component<Camera>();
            if (cam)
            {
                frame.view = cam->view_matrix(_active_camera->transform.position);
                frame.projection = cam->projection_matrix(aspect_ratio);
            }
        }

        renderer.begin_frame(frame);

        // Collect draw commands from MeshRenderers.
        for (const auto& entity : _entities)
        {
            if (!entity->is_active())
                continue;

            auto* mr = entity->get_component<MeshRenderer>();
            if (!mr)
                continue;

            rend::DrawCommand cmd{};
            cmd.vertex_buffer_info.id = mr->vbo;
            cmd.index_buffer_info.id = mr->ibo;
            cmd.index_buffer_info.count = mr->index_count;
            cmd.pipeline = mr->pipeline;
            cmd.texture = mr->texture;
            cmd.model_matrix = entity->transform.get_model_matrix();
            renderer.submit(cmd);
        }

        renderer.end_frame();
    }

    // --- Access ---

    const std::vector<std::unique_ptr<Entity>>& entities() const { return _entities; }

private:
    std::vector<std::unique_ptr<Entity>> _entities;
    Entity* _active_camera{nullptr};
};

} // namespace njin
