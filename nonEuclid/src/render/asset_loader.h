#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"
#include "texture.h"

using render::Shader;

class ShaderLoader
{
public:
    Shader CreateShader(const std::string& vert_path, const std::string& frag_path, const std::string& geom_path)
    {
        std::string vertexSource = _ReadFileToStr(vert_path);
        std::string geometrySource = "";
        if (geom_path != "") {
            geometrySource = _ReadFileToStr(geom_path);
        }
        std::string fragmentSource = _ReadFileToStr(frag_path);
        auto shader_program_id = _CreateShaderProgram(vertexSource, geometrySource, fragmentSource);
        return Shader(shader_program_id);
    }

private:
    std::string _ReadFileToStr(const std::string& file_path) {
        std::ifstream stream(file_path);
        std::stringstream string_stream;
        
        std::string line;
        while (getline(stream, line))
            string_stream << line << '\n';

        return string_stream.str();
    }  

    GLuint _CompileShader(unsigned int type, const std::string& source) {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << type << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(id);
            return 0;
        }
        return id;
    }

    GLuint _CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader)
    {
        GLuint program = glCreateProgram();
        GLuint vs, gs, fs;
        bool custom_geometry_shader = geometryShader.size();

        vs = _CompileShader(GL_VERTEX_SHADER, vertexShader);
        glAttachShader(program, vs);

        if (custom_geometry_shader) {
            GLuint gs = _CompileShader(GL_GEOMETRY_SHADER, geometryShader);
            glAttachShader(program, gs);
        }

        GLuint fs = _CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
        glAttachShader(program, fs);

        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);
        if (custom_geometry_shader)
            glDeleteShader(gs);

        return program;
    }
};
