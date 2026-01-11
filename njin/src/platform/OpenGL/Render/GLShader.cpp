#include "GLShader.hpp"

#include "logging.hpp"

#include <map>
#include <stdexcept>

namespace njin
{

std::unique_ptr<GLSubShader> GLSubShader::create(const std::string& src, GLuint shader_type)
{
    auto shaderID = glCreateShader(shader_type);
    auto c_src = static_cast<const GLchar*>(src.c_str());

    glShaderSource(shaderID, 1, &c_src, nullptr);
    glCompileShader(shaderID);
    
    GLint isCompiled{0};
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled != GL_TRUE)
    {
        GLint logLength{0};
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength)
        {
            std::vector<GLchar> infoLog(logLength);
            glGetShaderInfoLog(shaderID, logLength, &logLength, &infoLog[0]);
            njin::Logger::Error("Failed to compile GL shader: {}", infoLog.data());
        }
        else
            njin::Logger::Error("Failed to compile GL shader: No error log available");
        
        glDeleteShader(shaderID);
        return nullptr;
    }

    return std::unique_ptr<GLSubShader>(new GLSubShader(shaderID));
}



std::unique_ptr<Shader> GLShader::create(const std::string& vertex_src, const std::string& frag_src)
{
    auto vertShader = GLSubShader::create(vertex_src, GL_VERTEX_SHADER);
    auto fragShader = GLSubShader::create(frag_src, GL_FRAGMENT_SHADER);

    if (!vertShader || !fragShader)
        return nullptr;

    return create(vertShader.get(), fragShader.get());
}

std::unique_ptr<Shader> GLShader::create(GLSubShader* vertShader, GLSubShader* fragShader)
{
    if (!vertShader || !fragShader)
        return nullptr;

    auto vertID = vertShader->GetHandle();
    auto fragID = fragShader->GetHandle();

    auto id = glCreateProgram();
    glAttachShader(id, vertID);
    glAttachShader(id, fragID);
    glLinkProgram(id);

    GLint isLinked{0};
    glGetProgramiv(id, GL_LINK_STATUS, &isLinked);
    if (isLinked != GL_TRUE)
    {
        GLsizei infoSize;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoSize);
        if (infoSize)
        {
            std::vector<GLchar> log(infoSize);
            glGetProgramInfoLog(id, infoSize, &infoSize, &log[0]);
            njin::Logger::Error("Failed Linking GL Program with error: {}\n", log.data());
        }
        else
            njin::Logger::Error("Failed Linking GL Program with error: No error log available.\n");
        glDetachShader(id, fragID);
        glDetachShader(id, vertID);
        glDeleteProgram(id);
        return nullptr;
    }

    glDetachShader(id, fragID);
    glDetachShader(id, vertID);

    return std::unique_ptr<Shader>(new GLShader(id));
}


}