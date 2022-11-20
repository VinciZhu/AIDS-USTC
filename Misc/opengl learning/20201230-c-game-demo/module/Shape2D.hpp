#pragma once

#include "SystemModule.hpp"
#include "ShaderModule.hpp"
#include "TextureModule.hpp"

/*-----------------------------------------------------------------------------------------------*/
struct _Shape2D {
	const GLchar* const* shader_filenames;
	ShaderProgramInfo* program;
	const GLchar* const* tex_shader_filenames;
	ShaderProgramInfo* tex_program;
	GLuint position_loc;
	GLuint color_loc;
	GLuint tex_coord_loc;
	GLuint tex_binding;
	const GLchar* trans_mat_str;
	const GLchar* single_channel_str;
} * Shape2D;

void InitShape2D(const GLchar* const* shader_filenames, const GLchar* const* tex_shader_filenames,
	GLuint position_loc, GLuint color_loc, GLuint tex_coord_loc, GLuint tex_binding,
	const GLchar* trans_mat_str, const GLchar* single_channel_str);
void DestroyShape2D();
/*-----------------------------------------------------------------------------------------------*/

void InitShape2D(const GLchar* const* shader_filenames, const GLchar* const* tex_shader_filenames,
	GLuint position_loc, GLuint color_loc, GLuint tex_coord_loc, GLuint tex_binding,
	const GLchar* trans_mat_str, const GLchar* single_channel_str) {

	GLenum shader_types[] = {
		GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
	};
	FileProgramInfo* program = CreateFileProgram(shader_types, shader_filenames, 2);
	FileProgramInfo* tex_program = CreateFileProgram(shader_types, tex_shader_filenames, 2);
	glActiveTexture(GL_TEXTURE + tex_binding);

	Shape2D = new struct _Shape2D;
	Shape2D->shader_filenames = shader_filenames;
	Shape2D->program = program->program;
	Shape2D->tex_shader_filenames = tex_shader_filenames;
	Shape2D->tex_program = tex_program->program;
	Shape2D->position_loc = position_loc;
	Shape2D->color_loc = color_loc;
	Shape2D->tex_coord_loc = tex_coord_loc;
	Shape2D->tex_binding = tex_binding;
	Shape2D->trans_mat_str = trans_mat_str;
	Shape2D->single_channel_str = single_channel_str;
	delete program;
	delete tex_program;
}

void DestroyShape2D() {
	for (GLuint i = 0; i < Shape2D->program->shader_num; ++i) {
		DestroyShader(Shape2D->program->shaders[i]);
	}
	for (GLuint i = 0; i < Shape2D->tex_program->shader_num; ++i) {
		DestroyShader(Shape2D->tex_program->shaders[i]);
	}
	DestroyShaderProgram(Shape2D->program);
	DestroyShaderProgram(Shape2D->tex_program);
	delete Shape2D;
}