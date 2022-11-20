#pragma once

#include "SpriteBitmap.hpp"

/*-----------------------------------------------------------------------------------------------*/
typedef struct _FileBitmapInfo {
	SpriteBitmapInfo* bitmap;
	const GLchar* filename;
}FileBitmapInfo;

FileBitmapInfo* CreateFileBitmap(const GLchar* filename, GLuint x_num, GLuint y_num);

void DestroyFileBitmap(FileBitmapInfo* bitmap);
/*-----------------------------------------------------------------------------------------------*/
FileBitmapInfo* CreateFileBitmap(const GLchar* filename, GLuint x_num, GLuint y_num) {
	ImageTexInfo* image = CreateImageTex(GL_TEXTURE_2D, filename);
	FileBitmapInfo* bitmap = new FileBitmapInfo;
	bitmap->bitmap = CreateSpriteBitmap(image->tex, x_num, y_num);
	bitmap->filename = filename;
	delete image;
	return bitmap;
}

void DestroyFileBitmap(FileBitmapInfo* bitmap) {
	DestroyTexture(bitmap->bitmap->texture);
	DestroySpriteBitmap(bitmap->bitmap);
	delete bitmap;
}