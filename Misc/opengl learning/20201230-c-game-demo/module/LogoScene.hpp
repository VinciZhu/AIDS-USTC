#pragma once

#include "Scene.hpp"
/*-----------------------------------------------------------------------------------------------*/
struct _LogoScene {
	FPS_BoxInfo *fpsbox;
	TextBoxInfo *logo;
	AnimationInfo *animation;
} *LogoScene;
/*-----------------------------------------------------------------------------------------------*/

void LogoSceneKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (!FrameRender->is_freeze) {
		if (action = GLFW_PRESS && key == GLFW_KEY_ENTER || key == GLFW_KEY_SPACE) {
			SetGameScene(GameTitleScene);
			FadeOutGameGraphics(2.0);
			GameWait(2.0);
			FadeInGameGraphics(0.5);
			SetSystemWindowClearColor(GUI_Black);
		}
	}
}

void InitLogoScene() {

	GLfloat width = 1.0f * SystemWindow->width;
	GLfloat height = 1.0f * SystemWindow->height;


	FPS_BoxInfo* fpsbox = CreateFPS_Box(
		GUI_Rectangle, NULL, NULL, 0.0f, 0.0f, 0.0f, 80.0f, 24.0f,
		GUI_TransparentBlack, GL_TRUE,
		GUI_Horizontal, GUI_AlignCentre, GUI_AlignCentre,
		L"\\o2\\C4\\c6\\s16\\l16fps:"
	);


	TextBoxInfo* logo = CreateTextBox(
		GUI_Rectangle, NULL, NULL, width / 2, height / 2, 1.0f, width, height / 2,
		GUI_TransparentBlack, GL_TRUE,
		L"\\l96\\s80\\b5\\o\\c7L\\c8o\\c6g\\c2o",
		GUI_Horizontal, GUI_AlignCentre, GUI_AlignCentre
	);
	SetSpriteCentre(logo->sprite, width / 2, height / 4);
	SetSpriteCentre(logo->text_sprite, width / 2, height / 4);

	AnimationInfo *appear = CreateAnimation(GL_FALSE, GL_FALSE, GL_TRUE, GL_FALSE);
	AddAnimationKeyframe(appear, 0, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		GUI_TransparentWhite, GUI_TransparentWhite, 0.0, 0.0f);
	AddAnimationKeyframe(appear, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 2.0, -1.0f);
	AddSpriteAnimation(logo->text_sprite, appear);


	LogoScene = new struct _LogoScene;
	LogoScene->fpsbox = fpsbox;
	LogoScene->logo = logo;
	LogoScene->animation = appear;

	SetSystemKeyCallback(LogoSceneKeyCallback);
	SetSystemWindowClearColor(GUI_White);

}

void UpdateLogoScene() {
	if (!FrameRender->is_freeze && LogoScene->animation->is_paused) {
		SetGameScene(GameTitleScene);
		FadeOutGameGraphics(2.0);
		GameWait(2.0);
		SetSystemWindowClearColor(GUI_Black);
		FadeInGameGraphics(0.5);
	}
	else {
		UpdateFPS_Box(LogoScene->fpsbox);
		UpdateTextBox(LogoScene->logo);
	}
}

void DestroyLogoScene() {
	DestroyFPS_Box(LogoScene->fpsbox);
	DestroyTextBox(LogoScene->logo);
	DestroyAnimation(LogoScene->animation);
	delete LogoScene;
}
