#pragma once

#include "GameCore.hpp"

AnimationInfo *GameGraphicsFlashAnimation = NULL;
void UpdateGameGraphics() {
	if (GameGraphicsFlashAnimation && GameGraphicsFlashAnimation->is_paused) {
		FrameRender->screen_sprite->animations.erase(
			std::find(
				FrameRender->screen_sprite->animations.begin(),
				FrameRender->screen_sprite->animations.end(),
				GameGraphicsFlashAnimation
			)
		);
		DestroyAnimation(GameGraphicsFlashAnimation);
		GameGraphicsFlashAnimation = NULL;
	}
	RenderFrame();
	RefreshSystemWindow();
}
void GameWait(GLdouble duration) {
	while (!FrameRender->sprites.empty()) {
		FrameRender->sprites.pop();
	}
	FrameRender->is_freeze = GL_TRUE;
	GLdouble last_time = SystemTimer->cur;
	while (SystemTimer->cur - last_time < duration) {
		UpdateGameGraphics();
		UpdateGameCore();
	}
	FrameRender->is_freeze = GL_FALSE;
}
void FadeInGameGraphics(GLdouble duration) {
	if (GameGraphicsFlashAnimation) {
		FrameRender->screen_sprite->animations.erase(
			std::find(
				FrameRender->screen_sprite->animations.begin(),
				FrameRender->screen_sprite->animations.end(),
				GameGraphicsFlashAnimation
			)
		);
		DestroyAnimation(GameGraphicsFlashAnimation);
		GameGraphicsFlashAnimation = NULL;
	}
	GameGraphicsFlashAnimation = CreateAnimation(GL_FALSE, GL_FALSE, GL_TRUE, GL_FALSE);
	AddAnimationKeyframe(GameGraphicsFlashAnimation, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		glm::vec4(1.0f), SystemWindow->clear_color, 0.0f, 0.0f);
	AddAnimationKeyframe(GameGraphicsFlashAnimation, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		glm::vec4(1.0f), glm::vec4(0.0f), duration, 0.0f);
	AddSpriteAnimation(FrameRender->screen_sprite, GameGraphicsFlashAnimation);
}
void FadeOutGameGraphics(GLdouble duration) {
	if (GameGraphicsFlashAnimation) {
		FrameRender->screen_sprite->animations.erase(
			std::find(
				FrameRender->screen_sprite->animations.begin(),
				FrameRender->screen_sprite->animations.end(),
				GameGraphicsFlashAnimation
			)
		);
		DestroyAnimation(GameGraphicsFlashAnimation);
		GameGraphicsFlashAnimation = NULL;
	}
	GameGraphicsFlashAnimation = CreateAnimation(GL_FALSE, GL_FALSE, GL_TRUE, GL_FALSE);
	AddAnimationKeyframe(GameGraphicsFlashAnimation, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		glm::vec4(1.0f), glm::vec4(0.0f), 0.0f, 0.0f);
	AddAnimationKeyframe(GameGraphicsFlashAnimation, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		glm::vec4(1.0f), SystemWindow->clear_color, duration, 0.0f);
	AddSpriteAnimation(FrameRender->screen_sprite, GameGraphicsFlashAnimation);
}