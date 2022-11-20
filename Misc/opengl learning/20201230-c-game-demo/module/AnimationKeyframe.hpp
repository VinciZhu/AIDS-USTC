#pragma once

#include "SystemModule.hpp"

typedef struct _KeyframeInfo {
	GLuint bitmap_index;
	GLfloat x_offset, y_offset;
	GLfloat w_scale, h_scale;
	glm::vec4 tone;
	glm::vec4 flash_color;
	GLfloat angle;
	GLdouble interval;
	GLfloat delay;
}KeyframeInfo;

KeyframeInfo* CreateKeyframe(GLuint bitmap_index, GLfloat x_offset, GLfloat y_offset,
	GLfloat w_scale, GLfloat h_scale, GLfloat angle, glm::vec4 tone, glm::vec4 flash_color,
	GLdouble interval, GLfloat delay) {
	KeyframeInfo* keyframe = new KeyframeInfo;
	keyframe->bitmap_index = bitmap_index;
	keyframe->x_offset = x_offset;
	keyframe->y_offset = y_offset;
	keyframe->w_scale = w_scale;
	keyframe->h_scale = h_scale;
	keyframe->angle = angle;
	keyframe->tone = tone;
	keyframe->flash_color = flash_color;
	keyframe->interval = interval;
	keyframe->delay = delay;
	return keyframe;
}

void DestroyKeyframe(KeyframeInfo* keyframe) {
	delete keyframe;
}