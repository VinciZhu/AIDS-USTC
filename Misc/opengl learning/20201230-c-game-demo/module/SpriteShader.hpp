#pragma once

#include "SystemModule.hpp"
#include "Shape2D_Module.hpp"

struct _SpriteShader {
	const GLchar* const* filenames;
	ShaderProgramInfo* program;
	const GLchar* flash_color_str;

} * SpriteShader;

void InitSpriteShader(const GLchar* const* shader_filenames,  const GLchar* flash_color_str);

void DestroySpriteShader();
/*-----------------------------------------------------------------------------------------------*/
void InitSpriteShader(const GLchar* const* shader_filenames, const GLchar* flash_color_str) {
	GLenum shader_types[] = {
		GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
	};
	FileProgramInfo* program = CreateFileProgram(shader_types, shader_filenames, 2);
	SpriteShader = new struct _SpriteShader;
	SpriteShader->filenames = shader_filenames;
	SpriteShader->program = program->program;
	SpriteShader->flash_color_str = flash_color_str;
	delete program;
}

void DestroySpriteShader() {
	DestroyShaderProgram(SpriteShader->program);
	delete SpriteShader;
}