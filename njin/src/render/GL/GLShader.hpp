#pragma once

#include "logging.hpp"
#include "render/shader.hpp"

#include <exception>
#include <memory>

#include <glad/gl.h>

namespace njin
{

class GLSubShader 
{
private:
    GLSubShader(GLuint id)
    : _id(id)
    {}

public:
    ~GLSubShader()
    {
        glDeleteShader(_id);
    }
    
    static std::unique_ptr<GLSubShader> create(const std::string& src, GLuint shader_type);
    inline GLuint GetHandle() const { return _id; }

private:
    GLuint _id{0};
};



class GLShader: public Shader
{
private:
    GLShader(GLuint id) 
    : Shader()
    , _id(id)
    {}

public:
    static std::unique_ptr<Shader> create(const std::string& vertex_src, const std::string& frag_src);
    static std::unique_ptr<Shader> create(GLSubShader* vertShader, GLSubShader* fragShader);
    
    GLShader(const std::string& vertex_src, const std::string& frag_src)
    {
        auto vertShader = GLSubShader::create(vertex_src, GL_VERTEX_SHADER);
        auto fragShader = GLSubShader::create(frag_src, GL_FRAGMENT_SHADER);

        if (!vertShader || !fragShader)
            return;

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
            
            std::vector<GLchar> log(infoSize);
            glGetProgramInfoLog(id, infoSize, &infoSize, &log[0]);

            Logger::Error("Failed Linking GL Program with error: {}\n", log.data());
            glDetachShader(id, fragID);
            glDetachShader(id, vertID);
            glDeleteProgram(id);

            throw std::runtime_error("Failed to link GL shader\n");
        }

        glDetachShader(id, fragID);
        glDetachShader(id, vertID);

        _id = id;
    }

    ~GLShader()
    {
        glDeleteProgram(_id);
    }

    void Bind() override {
        glUseProgram(_id);
    }
    void UnBind() override {
        glUseProgram(0);
    }

    auto GetHandle() const { return _id; }

private:
    GLuint _id{0};
};


}