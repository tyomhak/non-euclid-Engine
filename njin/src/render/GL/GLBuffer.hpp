#pragma once

#include "buffer.hpp"

#include <glad/gl.h>

namespace njin
{

template<typename T, T type>
class GLBuffer : public Buffer
{
public:
    GLBuffer(size_t size)
    {
        
    }


private:
    GLuint _id{0};
};


};