#pragma once

#include "render/renderer_defines.hpp"

#include <string>
#include <unordered_map>
#include <optional>

namespace njin
{

/// Simple cache that maps file-system paths to renderer resource IDs.
/// Prevents duplicate loads of the same asset.
template<typename IDType>
class ResourceCache
{
public:
    /// Return the cached ID for the given path, or std::nullopt if not cached.
    std::optional<IDType> get(const std::string& path) const
    {
        auto it = _map.find(path);
        if (it != _map.end())
            return it->second;
        return std::nullopt;
    }

    /// Store a path → ID mapping.
    void put(const std::string& path, IDType id)
    {
        _map[path] = id;
    }

    /// Check if a path is already cached.
    bool contains(const std::string& path) const
    {
        return _map.find(path) != _map.end();
    }

    /// Remove a cached entry.
    void erase(const std::string& path)
    {
        _map.erase(path);
    }

    /// Clear all entries.
    void clear()
    {
        _map.clear();
    }

private:
    std::unordered_map<std::string, IDType> _map;
};

// Convenience typedefs.
using TextureCache  = ResourceCache<rend::TextureID>;
using ShaderCache   = ResourceCache<rend::ShaderID>;
using BufferCache   = ResourceCache<rend::BufferID>;
using PipelineCache = ResourceCache<rend::PipelineID>;

} // namespace njin
