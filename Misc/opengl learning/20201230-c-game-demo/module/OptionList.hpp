#pragma once
#pragma once

#include "TextBox.hpp"

/*-----------------------------------------------------------------------------------------------*/
typedef struct _OptionListInfo {
	GLuint options_num;
	GLuint cur_index;
	TextBoxInfo **options;
	FileBitmapInfo *cursor_bitmap;
	AnimationInfo *cursor_animation[2];
	SpriteInfo *cursor[2];
	GLenum direction;
	GLfloat spacing;
	GLboolean is_visible;
	GLboolean is_enabled;
} OptionListInfo;

OptionListInfo* CreateOptionList(GLenum appearance, SpriteBitmapInfo* bitmap, SpriteInfo* sup,
	GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, glm::vec4 tone, GLboolean is_visible,
	GLenum direction, GLenum x_align, GLenum y_align,
	GLuint options_num, std::wstring const *options_text,
	GLenum options_direction, GLfloat spacing, GLboolean is_enabled);

void UpdateOptionList(OptionListInfo* option_list);

void DestroyOptionList(OptionListInfo* option_list);

void SetOptionListOption(OptionListInfo* option_list, GLuint index);

void NextOptionListOption(OptionListInfo* option_list);

void PrevOptionListOption(OptionListInfo* option_list);

void OptionListKeyCallback(OptionListInfo* option_list, int key, int action);
/*-----------------------------------------------------------------------------------------------*/

OptionListInfo* CreateOptionList(GLenum appearance, SpriteBitmapInfo* bitmap, SpriteInfo* sup,
	GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, glm::vec4 tone, GLboolean is_visible,
	GLenum direction, GLenum x_align, GLenum y_align,
	GLuint options_num, std::wstring const *options_text,
	GLenum options_direction, GLfloat spacing, GLboolean is_enabled) {
	OptionListInfo* option_list = new OptionListInfo;
	option_list->options_num = options_num;
	option_list->cur_index = 0;
	option_list->options = new TextBoxInfo*[options_num];
	option_list->direction = options_direction;
	option_list->spacing = spacing;
	option_list->is_visible = is_visible;
	option_list->is_enabled = is_enabled;
	GLfloat ox = x, oy = y;
	for (GLuint i = 0; i < options_num; i++) {
		option_list->options[i] = CreateTextBox(appearance, bitmap, sup, ox, oy, z, w, h, tone, GL_TRUE,
			options_text[i], direction, x_align, y_align);
		switch (options_direction)
		{
		case GUI_Horizontal:
			ox += spacing;
			break;
		case GUI_Vertical:
			oy += spacing;
			break;
		default:
			break;
		}
	}
	option_list->cursor_bitmap = CreateFileBitmap(GetGameFile(GameGraphicsDir, GameOptionCursorFile), 1, 1);

	AnimationInfo *animation[2];
	animation[0] = CreateAnimation(GL_FALSE, GL_TRUE, GL_FALSE, GL_FALSE);
	animation[1] = CreateAnimation(GL_FALSE, GL_TRUE, GL_FALSE, GL_FALSE);
	AddAnimationKeyframe(animation[0], 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.0, 0.0f);
	AddAnimationKeyframe(animation[0], 0, -4.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.5, -1.0f);
	AddAnimationKeyframe(animation[0], 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.5, 1.0f);
	AddAnimationKeyframe(animation[0], 0, 4.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.5, -1.0f);
	AddAnimationKeyframe(animation[0], 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.5, 1.0f);
	option_list->cursor_animation[0] = animation[0];
	AddAnimationKeyframe(animation[1], 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.0, 0.0f);
	AddAnimationKeyframe(animation[1], 0, 4.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.5, -1.0f);
	AddAnimationKeyframe(animation[1], 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.5, 1.0f);
	AddAnimationKeyframe(animation[1], 0, -4.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.5, -1.0f);
	AddAnimationKeyframe(animation[1], 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		GUI_White, GUI_TransparentWhite, 0.5, 1.0f);
	option_list->cursor_animation[1] = animation[1];

	option_list->cursor[0] = CreateSprite(option_list->options[0]->sprite,
		option_list->cursor_bitmap->bitmap, 0,
		-24.0f, h / 2 - 12, 0.2f, 24.0f, 24.0f, 0.0f, GUI_White, GL_TRUE);
	option_list->cursor[1] = CreateSprite(option_list->options[0]->sprite,
		option_list->cursor_bitmap->bitmap, 0,
		w + 24.0f, h / 2 - 12, 0.2f, -24.0f, 24.0f, 0.0f, GUI_White, GL_TRUE);

	AddSpriteAnimation(option_list->cursor[0], animation[0]);
	AddSpriteAnimation(option_list->cursor[1], animation[1]);

	return option_list;
}

void UpdateOptionList(OptionListInfo* option_list) {
	if (option_list->is_visible) {
		for (GLuint i = 0; i < option_list->options_num; i++) {
			UpdateTextBox(option_list->options[i]);
		}
		if (option_list->is_enabled) {
			UpdateSprite(option_list->cursor[0]);
			UpdateSprite(option_list->cursor[1]);
		}
	}
}

void DestroyOptionList(OptionListInfo* option_list) {
	DestroyAnimation(option_list->cursor_animation[0]);
	DestroyAnimation(option_list->cursor_animation[1]);
	DestroySprite(option_list->cursor[0]);
	DestroySprite(option_list->cursor[1]);
	for (GLuint i = 0; i < option_list->options_num; i++) {
		DestroyTextBox(option_list->options[i]);
	}
	delete[] option_list->options;
	delete option_list;
}

void SetOptionListOption(OptionListInfo* option_list, GLuint index) {
	option_list->cursor[0]->sup = option_list->options[index]->sprite;
	option_list->cursor[1]->sup = option_list->options[index]->sprite;
	option_list->cur_index = index;
}

void NextOptionListOption(OptionListInfo* option_list) {
	GLuint index = option_list->cur_index + 1;
	if (index == option_list->options_num) index = 0; 
	SetOptionListOption(option_list, index);
}

void PrevOptionListOption(OptionListInfo* option_list) {
	GLuint index = option_list->cur_index - 1;
	if (index == -1) index += option_list->options_num;
	SetOptionListOption(option_list, index);
}

void OptionListKeyCallback(OptionListInfo* option_list, int key, int action) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_DOWN:
			NextOptionListOption(option_list);
			break;
		case GLFW_KEY_UP:
			PrevOptionListOption(option_list);
			break;
		case GLFW_KEY_LEFT:
			PrevOptionListOption(option_list);
			break;
		case GLFW_KEY_RIGHT:
			NextOptionListOption(option_list);
			break;
		default:
			break;
		}
	}
}