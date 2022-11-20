#pragma once

#include "OIT_Render.hpp"

struct SpritePtrCmpZ {
	bool operator()(SpriteInfo* a, SpriteInfo* b) {
		GLfloat z1=a->z, z2=b->z;
		while (a = a->sup)z1 += a->z;
		while (b = b->sup)z2 += b->z;
		return z1 > z2;
	}
};

struct _FrameRender {
	SpriteBitmapInfo *screen_bitmap;
	SpriteInfo *screen_sprite;
	std::priority_queue<struct _SpriteInfo*,
		std::vector<struct _SpriteInfo*>, SpritePtrCmpZ> sprites;
	std::queue<struct _SpriteInfo*> oit_sprites;
	GLboolean is_freeze;
} *FrameRender;

void InitFrameRender() {

	FrameRender = new struct _FrameRender;

	FrameRender->screen_bitmap = CreateDrawBitmap(SystemWindow->width, SystemWindow->height, 1, 1, 4);
	FrameRender->screen_sprite = CreateSprite(NULL, FrameRender->screen_bitmap, 0,
		0.0f, 1.0f * SystemWindow->height, 0.0f, 1.0f * SystemWindow->width, -1.0f * SystemWindow->height,
		0.0f, glm::vec4(1.0f), GL_TRUE);
	FrameRender->is_freeze = GL_FALSE;
	SetOIT_RenderTarget(FrameRender->screen_bitmap->texture);
}

void DestroyFrameRender() {
	DestroyDrawBitmap(FrameRender->screen_bitmap);
	DestroySprite(FrameRender->screen_sprite);
	delete FrameRender;
}

void UpdateSprite(SpriteInfo* sprite) {
	if (!FrameRender->is_freeze && sprite->is_visible) {
		FrameRender->sprites.push(sprite);
	}
}

void RenderFrame() {
	
	if (!FrameRender->is_freeze) {
		//渲染精灵
		BeginBitmapDraw(FrameRender->screen_bitmap);
		while (!FrameRender->sprites.empty()) {
			RenderSprite(FrameRender->sprites.top());
			FrameRender->sprites.pop();
		}
		EndBitmapDraw(FrameRender->screen_bitmap);
		//

		//渲染透明物体(此功能备用)
		BeginOIT_Render();


		EndOIT_Render();
		//
	}

	//渲染帧精灵
	RenderSprite(FrameRender->screen_sprite);
	//

}
