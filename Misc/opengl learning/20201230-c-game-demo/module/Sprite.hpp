#pragma once

#include "SpriteShader.hpp"
#include "SpriteBitmap.hpp"
#include "SpriteAnimation.hpp"

/*-----------------------------------------------------------------------------------------------*/
typedef struct _SpriteInfo {

	struct _SpriteInfo* sup;
	SpriteBitmapInfo* bitmap;
	GLuint bitmap_index;
	Quad2D_Info* quad;
	std::vector<AnimationInfo*> animations;
	GLfloat x, y, z;
	GLfloat w, h;
	GLfloat angle;
	glm::vec4 tone;
	glm::vec4 flash_color;
	glm::vec4 color;
	GLboolean is_visible;
	glm::mat4 trans_mat;

}SpriteInfo;

SpriteInfo* CreateSprite(SpriteInfo* sup, SpriteBitmapInfo* bitmap, GLuint bitmap_index,
	GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h,
	GLfloat angle, glm::vec4 tone, GLboolean is_visible);

void UpdateSprite(SpriteInfo* sprite);

void DrawSprite(SpriteInfo* sprite);

void DestroySprite(SpriteInfo* sprite);

void SetSpriteCentre(SpriteInfo* sprite, GLfloat ox, GLfloat oy);

void SetSpriteBitmapIndex(SpriteInfo* sprite, GLuint index);
/*-----------------------------------------------------------------------------------------------*/

SpriteInfo* CreateSprite( SpriteInfo* sup, SpriteBitmapInfo* bitmap, GLuint bitmap_index,
	GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h,
	GLfloat angle, glm::vec4 tone, GLboolean is_visible) {

	GLuint vbo = GenQuad2D_VBO();
	GLuint vao = GenQuad2D_VAO(vbo, Quad2D->ebo);
	Quad2D_Info* quad = CreateShapeQuad2D(
		0.0f, 1.0f * bitmap->h, tone, 1.0f * bitmap->w, 1.0f * bitmap->h, tone,
		1.0f * bitmap->w, 0.0f, tone, 0.0f, 0.0f, tone,
		0.0f, vao, vbo, SpriteShader->program);

	SpriteInfo* sprite = new SpriteInfo;
	sprite->sup = sup;
	sprite->bitmap = bitmap;
	sprite->quad = quad;
	SetSpriteBitmapIndex(sprite, bitmap_index);
	sprite->x = x;
	sprite->y = y;
	sprite->z = z;
	sprite->w = w;
	sprite->h = h;
	sprite->angle = angle;
	sprite->tone = tone;
	sprite->flash_color = glm::vec4();
	sprite->color = glm::vec4();
	sprite->is_visible = is_visible;
	sprite->trans_mat = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z))
		* glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

	return sprite;
}

void UpdateSpriteAnimation(SpriteInfo* sprite) {

	GLfloat x_offset = 0.0f, y_offset = 0.0f;
	GLfloat w_scale = 1.0f, h_scale = 1.0f;
	GLfloat angle = 0.0f;
	glm::vec4  tone = sprite->tone, flash_color = sprite->color;
	for (std::vector<AnimationInfo*>::iterator itr = sprite->animations.begin();
		itr != sprite->animations.end(); ++itr) {
		AnimationInfo* animation = *itr;
		if (!animation->is_paused) {
			KeyframeInfo* cur_frame = GetAnimationKeyframe(animation, 0);
			KeyframeInfo* next_frame = GetAnimationKeyframe(animation, 1);
			GLdouble interpo = cur_frame == next_frame ? 1.0 : glm::pow(
				(SystemTimer->cur - animation->last_time) / next_frame->interval,
				0.25 * next_frame->delay * (next_frame->delay + 3.0) + 1.0
			);
			if (interpo < 1) {
				x_offset += glm::mix(cur_frame->x_offset, next_frame->x_offset, interpo);
				y_offset += glm::mix(cur_frame->y_offset, next_frame->y_offset, interpo);
				w_scale *= glm::mix(cur_frame->w_scale, next_frame->w_scale, interpo);
				h_scale *= glm::mix(cur_frame->h_scale, next_frame->h_scale, interpo);
				angle += glm::mix(cur_frame->angle, next_frame->angle, interpo);
				tone *= glm::mix(cur_frame->tone, next_frame->tone, interpo);
				flash_color += glm::mix(cur_frame->flash_color, next_frame->flash_color, interpo);
			}
			else {
				if (NextAnimationKeyframe(animation) == 0 && animation->is_effective) {
					sprite->x += cur_frame->x_offset;
					sprite->y += cur_frame->y_offset;
					sprite->w *= cur_frame->w_scale;
					sprite->h *= cur_frame->h_scale;
					sprite->angle += cur_frame->angle;
					sprite->tone *= cur_frame->tone;
					sprite->color = cur_frame->flash_color;
				}
				else {
					x_offset += next_frame->x_offset;
					y_offset += next_frame->y_offset;
					w_scale *= next_frame->w_scale;
					h_scale *= next_frame->h_scale;
					angle += next_frame->angle;
					tone *= next_frame->tone;
					flash_color += next_frame->flash_color;
				}
			}
			if (animation->is_bitmap && sprite->bitmap_index != cur_frame->bitmap_index) {
				SetSpriteBitmapIndex(sprite, cur_frame->bitmap_index);
			}
		}
	}
	if (sprite->is_visible) {
		sprite->trans_mat = glm::translate(
			glm::mat4(1.0f),
			glm::vec3(sprite->x + x_offset, sprite->y + y_offset, sprite->z)
		) * glm::rotate(
			glm::mat4(1.0f),
			sprite->angle + angle,
			glm::vec3(0.0f, 0.0f, 1.0f)
		) * glm::scale(
			glm::mat4(1.0f),
			glm::vec3(w_scale, h_scale, 1.0f)
		);
		SetShapeQuad2D_Colors(sprite->quad, tone, tone, tone, tone);
		sprite->flash_color = flash_color;
	}
}

void RenderSprite(SpriteInfo* sprite) {
	UpdateSpriteAnimation(sprite);
	if (sprite->is_visible) {
		DrawSprite(sprite);
	}
}

void AddSpriteAnimation(SpriteInfo* sprite, AnimationInfo* animation) {
	sprite->animations.push_back(animation);
}

void DrawSprite(SpriteInfo* sprite) {
	if (sprite->sup) sprite->trans_mat = sprite->sup->trans_mat * sprite->trans_mat;
	glm::mat4 trans_mat = SystemWindow->ortho_mat
		* sprite->trans_mat
		* glm::scale(
			glm::mat4(1.0f),
			glm::vec3(sprite->w / sprite->bitmap->w, sprite->h / sprite->bitmap->h, 1.0f)
		);
	SetShaderVec4(SpriteShader->program, SpriteShader->flash_color_str, sprite->flash_color);
	DrawShapeQuad2D(sprite->quad, sprite->bitmap->texture, trans_mat);
}

void DestroySprite(SpriteInfo* sprite) {
	glDeleteBuffers(1, &sprite->quad->vbo);
	glDeleteVertexArrays(1, &sprite->quad->vao);
	DestroyShapeQuad2D(sprite->quad);
	delete sprite;
}

void SetSpriteCentre(SpriteInfo* sprite, GLfloat ox, GLfloat oy) {
	SetShapeQuad2D_Positions(sprite->quad,
		-ox, sprite->bitmap->h - oy,
		sprite->bitmap->w - ox, sprite->bitmap->h - oy,
		sprite->bitmap->w - ox, -oy,
		-ox, -oy, 0.0f);
};

void SetSpriteBitmapIndex(SpriteInfo* sprite, GLuint index) {
	sprite->bitmap_index = index;
	GLuint x_index = index % sprite->bitmap->x_num;
	GLuint y_index = index / sprite->bitmap->x_num;
	GLfloat x_delta = 1.0f / sprite->bitmap->x_num;
	GLfloat y_delta = 1.0f / sprite->bitmap->y_num;
	SetShapeQuad2D_TexCoords(sprite->quad,
		x_index * x_delta, (y_index + 1) * y_delta,
		(x_index + 1) * x_delta, (y_index + 1) * y_delta,
		(x_index + 1) * x_delta, y_index * y_delta,
		x_index * x_delta, y_index * y_delta
	);
};