#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader) 
{
    std::string vertexSource = ParseShader(vertexShader);
    std::string geometrySource = "";
    if (geometryShader != "") {
        geometrySource = ParseShader(geometryShader);
    }
    std::string fragmentSource = ParseShader(fragmentShader);
    _shader_program_id = CreateShader(vertexSource, geometrySource, fragmentSource);
}


std::string Shader::ParseShader(std::string filepath) {
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream stringStream;

    while (getline(stream, line))
    {
        stringStream << line << '\n';
    }

    return stringStream.str();
}


GLuint Shader::CompileShader(unsigned int type, const std::string& source) {
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


GLuint Shader::CreateShader(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader)
{
    GLuint program = glCreateProgram();
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    glAttachShader(program, vs);
    if (geometryShader != "") {
        GLuint gs = CompileShader(GL_GEOMETRY_SHADER, geometryShader);
        glAttachShader(program, gs);
    }
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}