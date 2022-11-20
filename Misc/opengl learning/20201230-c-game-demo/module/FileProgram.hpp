#pragma once

#include "ShaderProgram.hpp"
#include "FileShader.hpp"

/*-----------------------------------------------------------------------------------------------*/
typedef struct _FileProgramInfo {
	ShaderProgramInfo* program;
	const GLchar* const* filenames;
}FileProgramInfo;

FileProgramInfo* CreateFileProgram(const GLenum* types, const GLchar* const*  filenames, GLuint shader_num);

void DestroyFileProgram(FileProgramInfo* program);

/*-----------------------------------------------------------------------------------------------*/

FileProgramInfo* CreateFileProgram(const GLenum* types, const GLchar* const*  filenames, GLuint shader_num) {
	ShaderInfo** shaders = new ShaderInfo*[shader_num];
	for (GLuint i = 0; i < shader_num; ++i) {
		FileShaderInfo* file_shader = CreateFileShader(types[i], filenames[i]);
		shaders[i] = file_shader->shader;
		delete file_shader;
	}

	FileProgramInfo* program = new FileProgramInfo;
	program->program = CreateShaderProgram(shaders, shader_num);
	program->filenames = filenames;
	return program;
}

void DestroyFileProgram(FileProgramInfo* program) {
	for (GLuint i = 0; i < program->program->shader_num; ++i) {
		DestroyShader(program->program->shaders[i]);
	}
	DestroyShaderProgram(program->program);
	delete program;
}