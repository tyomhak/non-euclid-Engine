#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "utils/id.h"
#include "texture.h"
#include "material.h"

namespace render
{

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct Mesh
{
    std::vector<Mesh> children{};
    
    std::vector<Vertex> vertices{};
    std::vector<unsigned int> indices{};
    
    std::vector<ID<Texture>>    textures{};
    std::vector<ID<Material>>   material{};
    
    unsigned int VAO, VBO, EBO;
};

}