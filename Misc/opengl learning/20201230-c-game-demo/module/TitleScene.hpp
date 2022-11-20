#pragma once

#include "Scene.hpp"
/*-----------------------------------------------------------------------------------------------*/
struct _TitleScene {
	FPS_BoxInfo *fpsbox;
	TextBoxInfo *logo;
	TextBoxInfo *author_name;
	FileBitmapInfo *background_bitmap;
	SpriteInfo *background[2];
	AnimationInfo *logo_animation;
	AnimationInfo *author_name_animation;
	AnimationInfo *background_animation;
	OptionListInfo *commands;
} *TitleScene;
/*-----------------------------------------------------------------------------------------------*/

void TitleSceneKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (!FrameRender->is_freeze) {
		OptionListKeyCallback(TitleScene->commands, key, action);
		if (action = GLFW_PRESS && key == GLFW_KEY_SPACE || key == GLFW_KEY_ENTER) {
			switch (TitleScene->commands->cur_index)
			{
			case 0:
				SetGameScene(GameMiniGameScene);
				FadeOutGameGraphics(0.5);
				GameWait(0.5);
				FadeInGameGraphics(0.5);
				break;
			case 1:
				break;
			case 2:
				FadeOutGameGraphics(0.5);
				GameWait(1.0);
				SystemWindow->should_close = GL_TRUE;
				break;
			default:
				break;
			}
		}
	}
}

void InitTitleScene() {

	GLfloat width = 1.0f * SystemWindow->width;
	GLfloat height = 1.0f * SystemWindow->height;

	TextBoxInfo* logo = CreateTextBox(
		GUI_Rectangle, NULL, NULL, width / 2, height / 4, 1.0f, width, height / 2,
		GUI_TransparentBlack, GL_TRUE,
		L"\\b2\\C4\\o2\\s64还没有想好名字",
		GUI_Horizontal, GUI_AlignCentre, GUI_AlignCentre
	);
	SetSpriteCentre(logo->sprite, width / 2, height / 4);
	SetSpriteCentre(logo->text_sprite, width / 2, height / 4);

	AnimationInfo *swing = CreateAnimation(GL_FALSE, GL_TRUE, GL_FALSE, GL_FALSE);
	AddAnimationKeyframe(swing, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.0, 0.0f);
	AddAnimationKeyframe(swing, 0, 0.0f, 0.0f, 1.0f, 1.0f, glm::radians(2.0f),
		GUI_White, GUI_TransparentWhite, 1.0, -1.0f);
	AddAnimationKeyframe(swing, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 1.0, 1.0f);
	AddAnimationKeyframe(swing, 0, 0.0f, 0.0f, 1.0f, 1.0f, glm::radians(-2.0f),
		GUI_White, GUI_TransparentWhite, 1.0, -1.0f);
	AddAnimationKeyframe(swing, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 1.0, 1.0f);
	AddSpriteAnimation(logo->sprite, swing);

	TextBoxInfo* author_name = CreateTextBox(
		GUI_Rectangle, NULL, NULL, width * 3 / 4, height / 3, 2.0f, 150.0f, 48.0f,
		GUI_TransparentBlack, GL_TRUE,
		L"\\b1\\c6\\C4\\o1\\s24by hasined",
		GUI_Horizontal, GUI_AlignCentre, GUI_AlignTop
	);
	SetSpriteCentre(author_name->sprite, 75.0f, 24.0f);
	SetSpriteCentre(author_name->text_sprite, 75.0f, 24.0f);

	AnimationInfo *pop = CreateAnimation(GL_FALSE, GL_TRUE, GL_FALSE, GL_FALSE);
	AddAnimationKeyframe(pop, 0, 0.0f, 0.0f, 1.0f, 1.0f, glm::radians(-30.0f),
		GUI_White, GUI_TransparentWhite, 0.0, 0.0f);
	AddAnimationKeyframe(pop, 0, 0.0f, 0.0f, 1.2f, 1.2f, glm::radians(-30.0f),
		GUI_White, GUI_TransparentWhite, 0.5, -1.0f);
	AddAnimationKeyframe(pop, 0, 0.0f, 0.0f, 1.0f, 1.0f, glm::radians(-30.0f),
		GUI_White, GUI_TransparentWhite, 0.5, 1.0f);
	AddSpriteAnimation(author_name->sprite, pop);


	FileBitmapInfo* background_bitmap = CreateFileBitmap(
		GetGameFile(GameGraphicsDir, "Mountains1.png"), 1, 1);
	SpriteInfo* background[2];
	background[0] = CreateSprite(NULL, background_bitmap->bitmap, 0, 0.0f, 0.0f, 0.0f,
		width, height, 0.0f, GUI_White, GL_TRUE);
	background[1] = CreateSprite(background[0], background_bitmap->bitmap, 0, width, 0.0f, 0.0f,
		width, height, 0.0f, GUI_White, GL_TRUE);

	AnimationInfo *roll = CreateAnimation(GL_FALSE, GL_TRUE, GL_FALSE, GL_FALSE);
	AddAnimationKeyframe(roll, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.0, 0.0f);
	AddAnimationKeyframe(roll, 0, -width, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 20.0, 0.0f);
	AddSpriteAnimation(background[0], roll);


	FPS_BoxInfo* fpsbox = CreateFPS_Box(
		GUI_Rectangle, NULL, NULL, 0.0f, 0.0f, 2.0f, 80.0f, 24.0f,
		GUI_GetColor(GUI_Black, 0.8f), GL_TRUE,
		GUI_Horizontal, GUI_AlignCentre, GUI_AlignCentre,
		L"\\s16\\l16fps:"
	);

	std::wstring command_text[] = {
		GameNewGameStr,
		GameLoadGameStr,
		GameExitGameStr
	};

	OptionListInfo* commands = CreateOptionList(
		GUI_GradBar, NULL, NULL, width / 2 - 80.0f, height - 200.0f, 2.0f, 160.0f, 40.0f,
		GUI_Black, GL_TRUE,
		GUI_Horizontal, GUI_AlignCentre, GUI_AlignCentre,
		3, command_text, GUI_Vertical, 60.0f, GL_TRUE
	);

	TitleScene = new struct _TitleScene;
	TitleScene->fpsbox = fpsbox;
	TitleScene->logo = logo;
	TitleScene->author_name = author_name;
	TitleScene->background_bitmap = background_bitmap;
	TitleScene->background[0] = background[0];
	TitleScene->background[1] = background[1];
	TitleScene->background_animation = roll;
	TitleScene->logo_animation = swing;
	TitleScene->author_name_animation = pop;
	TitleScene->commands = commands;
	SetSystemKeyCallback(TitleSceneKeyCallback);
}

void UpdateTitleScene() {
	UpdateFPS_Box(TitleScene->fpsbox);
	UpdateTextBox(TitleScene->logo);
	UpdateTextBox(TitleScene->author_name);
	UpdateSprite(TitleScene->background[0]);
	UpdateSprite(TitleScene->background[1]);
	UpdateOptionList(TitleScene->commands);
}

void DestroyTitleScene() {
	DestroyFPS_Box(TitleScene->fpsbox);
	DestroyTextBox(TitleScene->logo);
	DestroySprite(TitleScene->background[0]);
	DestroySprite(TitleScene->background[1]);
	DestroyAnimation(TitleScene->background_animation);
	DestroyAnimation(TitleScene->logo_animation);
	DestroyAnimation(TitleScene->author_name_animation);
	DestroyOptionList(TitleScene->commands);
	delete TitleScene;
}
