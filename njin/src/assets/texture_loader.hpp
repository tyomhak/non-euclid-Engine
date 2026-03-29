#pragma once

#include "render/renderer.hpp"
#include "render/resource_descriptions.hpp"

#include <stb_image.h>

#include <string>
#include <stdexcept>

namespace njin
{

class TextureLoader
{
public:
    /// Load an image file and create a GPU texture through the renderer.
    /// Supports PNG, JPG, BMP, TGA, and other formats handled by stb_image.
    static rend::TextureID load(rend::Renderer& renderer, const std::string& path)
    {
        int width = 0, height = 0, channels = 0;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 4);
        if (!pixels)
            throw std::runtime_error("TextureLoader: failed to load '" + path + "': " + stbi_failure_reason());

        rend::TextureDesc desc{};
        desc.width  = static_cast<uint32_t>(width);
        desc.height = static_cast<uint32_t>(height);
        desc.format = rend::Format::RGBA8;
        desc.usage  = rend::TextureUsage::Sampled;
        desc.data   = pixels;

        auto id = renderer.create_texture(desc);

        stbi_image_free(pixels);
        return id;
    }
};

} // namespace njin
