#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "IncludeHeaders.h"

#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class Shader
{
public:
	Shader(string vertexShader, string geometryShader, string fragmentShader) {
		string vertexSource = ParseShader(vertexShader);
		string geometrySource = "";
		if (geometryShader != "") {
			geometrySource = ParseShader(geometryShader);
		}
		string fragmentSource = ParseShader(fragmentShader);
		ID = CreateShader(vertexSource, geometrySource, fragmentSource);
	}

	~Shader() {
		glDeleteProgram(ID);
	}

	void bind() {
		glUseProgram(ID);
	}

	void unbind() {
		glUseProgram(0);
	}

	std::string ParseShader(std::string filepath) {
		std::ifstream stream(filepath);
		std::string line;
		std::stringstream stringStream;

		while (getline(stream, line))
		{
			stringStream << line << '\n';
		}

		return stringStream.str();
	}
	GLuint  CompileShader(unsigned int type, const std::string& source) {
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

	GLuint CreateShader(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader)
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

	GLuint GetID() {
		return ID;
	}

	void update()
	{
		glm::mat4 mvp = projection * view * model;
		bind();
		SetMat4("mvp", mvp);
	}

	void SetVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}

	void SetVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	void SetVec3(const std::string& name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	void SetVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	void SetFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void SetInteger(const std::string& name, int value)
	{
		int i = glGetUniformLocation(ID, name.c_str());
		glUniform1i(i, value);
	}
	void SetMat3(const std::string& name, const glm::mat3& mat)
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void SetMat4(const std::string& name, const glm::mat4& mat)
	{
		int i = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void setView(glm::mat4 _view)
	{
		view = _view;
	}

	void setModel(glm::mat4 _model)
	{
		model = _model;
	}

	void setProjection(glm::mat4 _projection)
	{
		projection = _projection;
	}

public:
	GLuint ID;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 projection;

};

#endif