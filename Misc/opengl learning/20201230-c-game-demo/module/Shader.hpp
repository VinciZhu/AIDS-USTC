#pragma once

#include "SystemModule.hpp"

/*-----------------------------------------------------------------------------------------------*/
typedef struct _ShaderInfo {
	GLuint name;
	GLenum type;
	const GLchar* src;
}ShaderInfo;

ShaderInfo* CreateShader(GLenum type, const GLchar* src);

void DestroyShader(ShaderInfo* shader);
/*-----------------------------------------------------------------------------------------------*/

ShaderInfo* CreateShader(GLenum type, const GLchar* src) {
	GLuint name = glCreateShader(type);
	glShaderSource(name, 1, &src, NULL);
	glCompileShader(name);
	GLint is_compiled;
	glGetShaderiv(name, GL_COMPILE_STATUS, &is_compiled);
	if (!is_compiled) {
#ifdef _DEBUG
		GLsizei loglen;
		glGetShaderiv(name, GL_INFO_LOG_LENGTH, &loglen);
		GLchar* log = (GLchar*)malloc(sizeof(GLchar)*(loglen + 1));
		glGetShaderInfoLog(name, loglen, &loglen, log);
		std::cerr << "Error: shader compilation failed" << std::endl << log;
		free(log);
#endif // _DEBUG
	}

	ShaderInfo* shader = new ShaderInfo;
	shader->name = name;
	shader->src = src;

	return shader;
}

void DestroyShader(ShaderInfo* shader) {
	glDeleteShader(shader->name);
	delete shader;
}
