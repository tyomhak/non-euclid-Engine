#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "render/render_engine.h"

namespace render
{

class Shader
{
public:
    Shader(GLuint shader_program_id) : _shader_program_id(shader_program_id)
    {}

    void SetFloat(const std::string& name, float value)
    {
        glUniform1f(glGetUniformLocation(_shader_program_id, name.c_str()), value);
    }
    void SetInteger(const std::string& name, int value)
    {
        int i = glGetUniformLocation(_shader_program_id, name.c_str());
        glUniform1i(i, value);
    }
    
    void SetVec3(const std::string& name, const glm::vec3& value)
    {
        glUniform3fv(glGetUniformLocation(_shader_program_id, name.c_str()), 1, &value[0]);
    }
    void SetVec4(const std::string& name, const glm::vec4& value)
    {
        glUniform4fv(glGetUniformLocation(_shader_program_id, name.c_str()), 1, &value[0]);
    }

    void SetMat3(const std::string& name, const glm::mat3& mat)
    {
        glUniformMatrix3fv(glGetUniformLocation(_shader_program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void SetMat4(const std::string& name, const glm::mat4& mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(_shader_program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
	GLuint _shader_program_id;
};


}