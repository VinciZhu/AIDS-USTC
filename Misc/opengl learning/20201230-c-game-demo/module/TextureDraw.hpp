#pragma once

#include "Texture.hpp"

/*-----------------------------------------------------------------------------------------------*/
struct _TextureDraw {

	GLuint fbo;
	glm::mat4 ortho_mat;

	GLint viewport_temp[4];

} *TextureDraw;

void InitTextureDraw();

void DestroyTextureDraw();

void BeginDrawTex(TexInfo* texture, GLboolean is_clear);

void EndDrawTex(TexInfo* texture);
/*-----------------------------------------------------------------------------------------------*/

void InitTextureDraw() {
	GLuint fbo;
	glCreateFramebuffers(1, &fbo);

	TextureDraw = new struct _TextureDraw;
	TextureDraw->fbo = fbo;
	TextureDraw->ortho_mat = glm::ortho(
		0.0f, 1.0f * SystemWindow->width,
		0.0f, 1.0f * SystemWindow->height,
		-1.0f * SystemWindow->depth, 0.0f
	);
}

void DestroyTextureDraw() {
	glDeleteFramebuffers(1, &TextureDraw->fbo);
	delete TextureDraw;
}

void BeginDrawTex(TexInfo* texture, GLboolean is_clear = GL_TRUE) {
	glGetIntegerv(GL_VIEWPORT, TextureDraw->viewport_temp);
	glBindFramebuffer(GL_FRAMEBUFFER, TextureDraw->fbo);
	glNamedFramebufferTexture(TextureDraw->fbo, GL_COLOR_ATTACHMENT0, texture->name, 0);
	glViewport(0, 0, SystemWindow->width, SystemWindow->height);
	if (is_clear) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void EndDrawTex(TexInfo* texture) {
	glGenerateTextureMipmap(texture->name);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(SystemWindow->clear_color.r, SystemWindow->clear_color.g,
		SystemWindow->clear_color.b, SystemWindow->clear_color.a);
	glViewport(TextureDraw->viewport_temp[0], TextureDraw->viewport_temp[1],
		TextureDraw->viewport_temp[2], TextureDraw->viewport_temp[3]);
}