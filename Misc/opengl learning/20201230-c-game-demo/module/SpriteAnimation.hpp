#pragma once

#include "AnimationKeyframe.hpp"

/*-----------------------------------------------------------------------------------------------*/
typedef struct _AnimationInfo {
	GLboolean is_paused;
	GLboolean is_loop;
	GLboolean is_effective;
	GLboolean is_bitmap;
	std::vector<KeyframeInfo*> keyframes;
	GLuint cur_index;
	GLdouble last_time;
}AnimationInfo;

AnimationInfo* CreateAnimation(GLboolean is_paused, GLboolean is_loop, GLboolean is_effective, GLboolean is_bitmap);

void DestroyAnimation(AnimationInfo* animation);

void SetAnimationLoop(AnimationInfo* animation, GLboolean is_loop);

void AddAnimationKeyframe(AnimationInfo* animation, GLuint bitmap_index, GLfloat x, GLfloat y,
	GLfloat w, GLfloat h, GLfloat angle, glm::vec4 tone, glm::vec4 flash_color,
	GLdouble interval, GLfloat delay);

GLuint NextAnimationKeyframe(AnimationInfo* animation);
/*-----------------------------------------------------------------------------------------------*/
AnimationInfo* CreateAnimation(GLboolean is_paused, GLboolean is_loop, GLboolean is_effective, GLboolean is_bitmap) {
	AnimationInfo* animation = new AnimationInfo;
	animation->is_paused = is_paused;
	animation->is_loop = is_loop;
	animation->is_effective = is_effective;
	animation->is_bitmap = is_bitmap;
	animation->cur_index = 0;
	animation->last_time = SystemTimer->cur;
	return animation;
}

void DestroyAnimation(AnimationInfo* animation) {
	for (std::vector<KeyframeInfo*>::iterator itr = animation->keyframes.begin();
		itr != animation->keyframes.end(); ++itr) {
		DestroyKeyframe(*itr);
	}
	delete animation;
}

void SetAnimationLoop(AnimationInfo* animation, GLboolean is_loop) {
	animation->is_loop = is_loop;
}

void AddAnimationKeyframe(AnimationInfo* animation, GLuint bitmap_index, GLfloat x, GLfloat y,
	GLfloat w, GLfloat h, GLfloat angle, glm::vec4 tone, glm::vec4 flash_color,
	GLdouble interval, GLfloat delay) {

	KeyframeInfo* keyframe = CreateKeyframe(bitmap_index, x, y, w, h,
		angle, tone, flash_color, interval, delay);
	animation->keyframes.push_back(keyframe);
}

KeyframeInfo *GetAnimationKeyframe(AnimationInfo* animation, GLint offset) {
	GLuint index = animation->cur_index;
	while (offset < 0) {
		++offset;
		if (index == 0) break;
		else --index;
	}
	while (offset > 0) {
		--offset;
		if (index == animation->keyframes.size() - 1) break;
		else ++index;
	}
	return animation->keyframes[index];
}

GLuint NextAnimationKeyframe(AnimationInfo* animation) {
	animation->last_time = SystemTimer->cur;
	++animation->cur_index;
	if (animation->cur_index == animation->keyframes.size()) {
		animation->cur_index = 0;
		if (!animation->is_loop) {
			animation->is_paused = GL_TRUE;
		}
	}
	return animation->cur_index;
}

void PauseAnimation(AnimationInfo* animation) {
	animation->is_paused = GL_TRUE;
}

void StopAnimation(AnimationInfo* animation) {
	animation->cur_index = 0; 
	PauseAnimation(animation);
}

void PlayAnimation(AnimationInfo* animation) {
	animation->is_paused = GL_FALSE;
	animation->last_time = SystemTimer->cur;
}

void StartAnimation(AnimationInfo* animation) {
	animation->cur_index = 0; 
	PlayAnimation(animation);
}
