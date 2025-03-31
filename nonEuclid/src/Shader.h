#pragma once

#include <string>

#include <glad/gl.h>
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
public:
	Shader(const std::string& vertexShader, 
		const std::string& geometryShader, 
		const std::string& fragmentShader);

	~Shader() {
		glDeleteProgram(_shader_program_id);
	}

	void Bind() {
		glUseProgram(_shader_program_id);
	}

	void Unbind() {
		glUseProgram(0);
	}

	GLuint GetProgramID() const { return _shader_program_id; }

	std::string ParseShader(std::string filepath);
	GLuint CompileShader(unsigned int type, const std::string& source);

	GLuint CreateShader(const std::string& vertexShader, 
		const std::string& geometryShader, 
		const std::string& fragmentShader);


	void Update()
	{
		glm::mat4 mvp = projection * view * model;
		SetMat4("mvp", mvp);
	}

	void SetVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(_shader_program_id, name.c_str()), x, y, z, w);
	}

	void SetVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(glGetUniformLocation(_shader_program_id, name.c_str()), 1, &value[0]);
	}

	void SetVec3(const std::string& name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(_shader_program_id, name.c_str()), x, y, z);
	}

	void SetVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(_shader_program_id, name.c_str()), 1, &value[0]);
	}

	void SetFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(_shader_program_id, name.c_str()), value);
	}

	void SetInteger(const std::string& name, int value)
	{
		int i = glGetUniformLocation(_shader_program_id, name.c_str());
		glUniform1i(i, value);
	}
	void SetMat3(const std::string& name, const glm::mat3& mat)
	{
		glUniformMatrix3fv(glGetUniformLocation(_shader_program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void SetMat4(const std::string& name, const glm::mat4& mat)
	{
		glUniformMatrix4fv(glGetUniformLocation(_shader_program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void SetView(const glm::mat4& _view)
	{
		view = _view;
	}

	void SetModel(const glm::mat4& _model)
	{
		model = _model;
	}

	void SetProjection(const glm::mat4& _projection)
	{
		projection = _projection;
	}

private:
	GLuint _shader_program_id;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 projection;
};
