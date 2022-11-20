#pragma once

#include "SystemModule.hpp"
#include "Shape2D_Module.hpp"

/*-----------------------------------------------------------------------------------------------*/
typedef struct _SpriteBitmapInfo {
	GLuint x_num, y_num;
	GLuint index_num;
	TexInfo* texture;
	GLuint w, h;
	GLboolean is_single_channel;
}SpriteBitmapInfo;

SpriteBitmapInfo* CreateSpriteBitmap(TexInfo* texture, GLuint x_num, GLuint y_num);

void DestroySpriteBitmap(SpriteBitmapInfo* bitmap);
/*-----------------------------------------------------------------------------------------------*/
SpriteBitmapInfo* CreateSpriteBitmap(TexInfo* texture, GLuint x_num, GLuint y_num) {
	SpriteBitmapInfo* bitmap = new SpriteBitmapInfo;
	GLuint w = texture->width / x_num;
	GLuint h = texture->height / y_num;
	bitmap->x_num = x_num;
	bitmap->y_num = y_num;
	bitmap->index_num = x_num * y_num;
	bitmap->texture = texture;
	bitmap->w = w;
	bitmap->h = h;
	bitmap->is_single_channel = texture->channels_num == 1;
	return bitmap;
}

void DestroySpriteBitmap(SpriteBitmapInfo* bitmap) {
	delete bitmap;
}