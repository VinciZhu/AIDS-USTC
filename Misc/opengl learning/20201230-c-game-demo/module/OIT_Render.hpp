#pragma once

#include "SpriteModule.hpp"

struct _OIT_Render {
	GLuint frag_buf;
	GLuint frag_tex;
	GLuint counter_buf;
	GLuint head_ptr_tex;
	GLuint head_ptr_pbo;

	const GLchar* render_shader_files;
	ShaderProgramInfo* render_program;

	const GLchar* sprite_shader_files;
	ShaderProgramInfo* sprite_program;

	TexInfo *target;
	Quad2D_Info *target_quad;

} *OIT_Render;

void InitOIT_Render(const GLchar* const* render_shader_files, const GLchar* const* sprite_shader_files) {
	OIT_Render = new struct _OIT_Render;

	glCreateBuffers(1, &OIT_Render->frag_buf);
	glNamedBufferStorage(OIT_Render->frag_buf, 2 * SystemWindow->pixels_num * sizeof(glm::uvec4),
		NULL, NULL);
	glCreateTextures(GL_TEXTURE_BUFFER, 1, &OIT_Render->frag_tex);
	glTextureBuffer(OIT_Render->frag_tex, GL_RGBA32UI, OIT_Render->frag_buf);

	glCreateBuffers(1, &OIT_Render->counter_buf);
	glNamedBufferStorage(OIT_Render->counter_buf, sizeof(GLuint),
		NULL, GL_MAP_WRITE_BIT);

	glCreateTextures(GL_TEXTURE_2D, 1, &OIT_Render->head_ptr_tex);
	glTextureStorage2D(OIT_Render->head_ptr_tex, 1, GL_R32UI,
		SystemWindow->width, SystemWindow->height);
	glTextureSubImage2D(OIT_Render->head_ptr_tex, 0, 0, 0,
		SystemWindow->width, SystemWindow->height, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);
	glTextureParameteri(OIT_Render->head_ptr_tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(OIT_Render->head_ptr_tex, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTextureParameteri(OIT_Render->head_ptr_tex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(OIT_Render->head_ptr_tex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	glCreateBuffers(1, &OIT_Render->head_ptr_pbo);
	glNamedBufferStorage(OIT_Render->head_ptr_pbo, SystemWindow->pixels_num * sizeof(GLuint),
		NULL, GL_MAP_WRITE_BIT);
	GLuint *data = (GLuint*)glMapNamedBuffer(OIT_Render->head_ptr_pbo, GL_WRITE_ONLY);
	memset(data, 0x00, SystemWindow->pixels_num * sizeof(GLuint));
	glUnmapNamedBuffer(OIT_Render->head_ptr_pbo);

	GLenum render_shader_types[] = {
		GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
	};
	FileProgramInfo* render_program = CreateFileProgram(render_shader_types, render_shader_files, 2);
	OIT_Render->render_program = render_program->program;
	delete render_program;

	GLenum sprite_shader_types[] = {
		GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
	};
	FileProgramInfo* sprite_program = CreateFileProgram(sprite_shader_types, sprite_shader_files, 2);
	OIT_Render->sprite_program = sprite_program->program;
	delete sprite_program;

	OIT_Render->target = NULL;
	OIT_Render->target_quad = NULL;

}

void DestroyOIT_Render() {
	DestroyShapeQuad2D(OIT_Render->target_quad);
	DestroyShaderProgram(OIT_Render->sprite_program);
	glDeleteBuffers(1, &OIT_Render->head_ptr_pbo);
	glDeleteTextures(1, &OIT_Render->head_ptr_tex);
	glDeleteBuffers(1, &OIT_Render->counter_buf);
	glDeleteTextures(1, &OIT_Render->frag_tex);
	glDeleteBuffers(1, &OIT_Render->frag_buf);
	delete OIT_Render;
}

void SetOIT_RenderTarget(TexInfo *target) {
	OIT_Render->target = target;
	glm::vec4 color(1.0f);
	OIT_Render->target_quad = CreateShapeQuad2D(
		0.0f, 1.0f * target->height, color,
		1.0f * target->width, 1.0f * target->height, color,
		1.0f * target->width, 0.0f, color,
		0.0f, 0.0f, color,
		0.0f, Quad2D->vao, Quad2D->vbo, OIT_Render->render_program
	);
}

void BeginOIT_Render() {
	GLuint *data = (GLuint*)glMapNamedBuffer(OIT_Render->counter_buf, GL_WRITE_ONLY);
	*data = 0U;
	glUnmapNamedBuffer(OIT_Render->counter_buf);
	glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, OIT_Render->counter_buf);

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, OIT_Render->head_ptr_pbo);
	glTextureSubImage2D(OIT_Render->head_ptr_tex, 0, 0, 0,
		SystemWindow->width, SystemWindow->height, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

	glBindImageTexture(2, OIT_Render->frag_tex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32UI);
	glBindImageTexture(1, OIT_Render->head_ptr_tex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI);

}

void EndOIT_Render() {
	glClear(GL_DEPTH_BUFFER_BIT);
	BeginDrawTex(OIT_Render->target, GL_FALSE);
	DrawShapeQuad2D(OIT_Render->target_quad, OIT_Render->target, TextureDraw->ortho_mat);
	EndDrawTex(OIT_Render->target);
}