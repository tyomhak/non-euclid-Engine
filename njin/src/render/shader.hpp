#pragma once

#include <vector>
#include <string>

namespace njin
{
    class Shader
    {
    public:
        virtual ~Shader() = default;
        
        virtual void Bind() = 0;
        virtual void UnBind() = 0;
    
    protected:
        Shader() = default;
    };
};