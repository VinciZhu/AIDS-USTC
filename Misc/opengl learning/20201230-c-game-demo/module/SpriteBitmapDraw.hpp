#pragma once

#include "SpriteBitmap.hpp"
#include "TextureDraw.hpp"

/*-----------------------------------------------------------------------------------------------*/
struct _BitmapDraw {
	GLuint fbo;
	glm::mat4 ortho_mat;
} * BitmapDraw;

SpriteBitmapInfo* CreateDrawBitmap(GLuint w, GLuint h, GLuint x_num, GLuint y_num, GLuint channels_num);

void DestroyDrawBitmap(SpriteBitmapInfo* bitmap);

void InitBitmapDraw();

void DestroyBitmapDraw();

void BeginBitmapDraw(SpriteBitmapInfo* bitmap);

void EndBitmapDraw(SpriteBitmapInfo* bitmap);
/*-----------------------------------------------------------------------------------------------*/

SpriteBitmapInfo* CreateDrawBitmap(GLuint w, GLuint h, GLuint x_num, GLuint y_num, GLuint channels_num) {
	TexInfo* tex = CreateTexture(GL_TEXTURE_2D, NULL, w * x_num, h * y_num, channels_num);
	SpriteBitmapInfo* bitmap = CreateSpriteBitmap(tex, x_num, y_num);
	return bitmap;
}

void DestroyDrawBitmap(SpriteBitmapInfo* bitmap) {
	DestroyTexture(bitmap->texture);
	DestroySpriteBitmap(bitmap);
}

void InitBitmapDraw() {
	BitmapDraw = new struct _BitmapDraw;
	BitmapDraw->fbo = TextureDraw->fbo;
	BitmapDraw->ortho_mat = TextureDraw->ortho_mat;
}

void DestroyBitmapDraw() {
	delete BitmapDraw;
}

void BeginBitmapDraw(SpriteBitmapInfo* bitmap) {
	BeginDrawTex(bitmap->texture);
}

void EndBitmapDraw(SpriteBitmapInfo* bitmap) {
	EndDrawTex(bitmap->texture);
}