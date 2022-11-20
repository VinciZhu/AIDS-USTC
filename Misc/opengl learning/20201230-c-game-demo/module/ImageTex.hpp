#pragma once

#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

/*-----------------------------------------------------------------------------------------------*/
typedef struct _ImageTexInfo {
	TexInfo* tex;
	const GLchar* filename;
}ImageTexInfo;

ImageTexInfo* CreateImageTex(GLenum type, const GLchar* filename);

void DestroyImageTex();
/*-----------------------------------------------------------------------------------------------*/

ImageTexInfo* CreateImageTex(GLenum type, const GLchar* filename) {
	GLint width, height, channels_num;
	GLubyte* image = stbi_load(filename, &width, &height, &channels_num, 0);
	if (!image) {
#ifdef _DEBUG
		std::cerr << "Error: fail to load " << filename << std::endl;
#endif // _DEBUG
	}

	ImageTexInfo* texture = new ImageTexInfo;
	texture->tex = CreateTexture(type, image, width, height, channels_num);
	texture->tex->width = width;
	texture->tex->height = height;

	stbi_image_free(image);
	return texture;
}

void DestroyImageTex(ImageTexInfo* texture) {
	DestroyTexture(texture->tex);
	delete texture;
}