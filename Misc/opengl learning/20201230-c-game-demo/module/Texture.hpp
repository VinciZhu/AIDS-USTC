#pragma once

#include "SystemModule.hpp"

/*-----------------------------------------------------------------------------------------------*/
const glm::vec2 TexBottomLeft = glm::vec2(0.0f, 1.0f);
const glm::vec2 TexBottomRight = glm::vec2(1.0f, 1.0f);
const glm::vec2 TexTopRight = glm::vec2(1.0f, 0.0f);
const glm::vec2 TexTopLeft = glm::vec2(0.0f, 0.0f);

typedef struct _TexInfo {
	GLuint name;
	GLenum type;
	const GLubyte* src;
	GLsizei width;
	GLsizei height;
	GLuint channels_num;
}TexInfo;

TexInfo* CreateTexture(GLenum type, const GLubyte* src, GLsizei width, GLsizei height, GLuint channels_num);

void DestroyTexture(TexInfo* texture);
/*-----------------------------------------------------------------------------------------------*/

TexInfo* CreateTexture(GLenum type, const GLubyte* src, GLsizei width, GLsizei height, GLuint channels_num) {
	GLuint name;
	glCreateTextures(type, 1, &name);

	switch (channels_num)
	{
	case 1:
		glTextureStorage2D(name, 1, GL_R8, width, height);
		glTextureSubImage2D(name, 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE, src);
		break;
	case 3:
		glTextureStorage2D(name, 1, GL_RGB8, width, height);
		glTextureSubImage2D(name, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, src);
		break;
	case 4:
		glTextureStorage2D(name, 1, GL_RGBA8, width, height);
		glTextureSubImage2D(name, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, src);
		break;
	default:
		break;
	}

	glTextureParameteri(name, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(name, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTextureParameteri(name, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(name, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	if (src) {
		glGenerateTextureMipmap(name);
	}

	TexInfo* texture = new TexInfo;
	texture->name = name;
	texture->type = type;
	texture->src = src;
	texture->width = width;
	texture->height = height;
	texture->channels_num = channels_num;

	return texture;
}

void DestroyTexture(TexInfo* texture) {
	glDeleteTextures(1, &texture->name);
	delete texture;
}