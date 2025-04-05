#pragma once

#include <string>

namespace render
{

enum class TextureType
{
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT,
};

struct Texture 
{
    unsigned int internal_id;
    std::string path;
    TextureType type;
};




}