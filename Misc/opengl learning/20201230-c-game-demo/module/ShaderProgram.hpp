#pragma once

#include "Shader.hpp"

/*-----------------------------------------------------------------------------------------------*/
typedef struct _ShaderProgramInfo {
	GLuint name;
	ShaderInfo** shaders;
	GLuint shader_num;
}ShaderProgramInfo;

ShaderProgramInfo* CreateShaderProgram(ShaderInfo** shaders, GLuint shader_num);

void DestroyShaderProgram(ShaderProgramInfo* program);

void UseShaderProgram(ShaderProgramInfo* program);

void SetShaderVec4(ShaderProgramInfo* program, const GLchar* dest, glm::vec4 src);

void SetShaderMat4(ShaderProgramInfo* program, const GLchar* dest, glm::mat4 src);

void SetShaderBool(ShaderProgramInfo* program, const GLchar* dest, GLboolean src);

void SetShaderInt(ShaderProgramInfo* program, const GLchar* dest, GLint src);

void SetShaderUInt(ShaderProgramInfo* program, const GLchar* dest, GLuint src);
/*-----------------------------------------------------------------------------------------------*/

ShaderProgramInfo* CreateShaderProgram(ShaderInfo** shaders, GLuint shader_num) {
	GLuint name = glCreateProgram();
	for (GLuint i = 0; i < shader_num; ++i) {
		glAttachShader(name, shaders[i]->name);
	}
	glLinkProgram(name);
	GLint is_linked;
	glGetProgramiv(name, GL_LINK_STATUS, &is_linked);
	if (!is_linked) {
#ifdef _DEBUG
		GLsizei loglen;
		glGetProgramiv(name, GL_INFO_LOG_LENGTH, &loglen);
		GLchar* log = (GLchar*)malloc(sizeof(GLchar)*(loglen + 1));
		glGetProgramInfoLog(name, loglen, &loglen, log);
		std::cerr << "Error: shader program linking failed" << std::endl << log;
		free(log);
#endif // _DEBUG
	}

	ShaderProgramInfo* program = new ShaderProgramInfo;
	program->name = name;
	program->shaders = shaders;
	program->shader_num = shader_num;

	return program;
}

void DestroyShaderProgram(ShaderProgramInfo* program) {
	glDeleteProgram(program->name);
	delete program;
}

void UseShaderProgram(ShaderProgramInfo* program) {
	glUseProgram(program->name);
}

void SetShaderVec4(ShaderProgramInfo* program, const GLchar* dest, glm::vec4 src) {
	glProgramUniform4fv(program->name, glGetUniformLocation(program->name, dest),
		1, glm::value_ptr(src));
}

void SetShaderMat4(ShaderProgramInfo* program, const GLchar* dest, glm::mat4 src) {
	glProgramUniformMatrix4fv(program->name, glGetUniformLocation(program->name, dest),
		1, GL_FALSE, glm::value_ptr(src));
}

void SetShaderBool(ShaderProgramInfo* program, const GLchar* dest, GLboolean src) {
	glProgramUniform1i(program->name, glGetUniformLocation(program->name, dest), src);
}

void SetShaderInt(ShaderProgramInfo* program, const GLchar* dest, GLint src) {
	glProgramUniform1i(program->name, glGetUniformLocation(program->name, dest), src);
}

void SetShaderUInt(ShaderProgramInfo* program, const GLchar* dest, GLuint src) {
	glProgramUniform1ui(program->name, glGetUniformLocation(program->name, dest), src);
}
