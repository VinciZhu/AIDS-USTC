#pragma once

#include "TextBox.hpp"

/*-----------------------------------------------------------------------------------------------*/
typedef struct _FPS_BoxInfo {
	TextBoxInfo *text;
	std::wstring style;
	GLboolean is_visible;
} FPS_BoxInfo;

FPS_BoxInfo* CreateFPS_Box(GLenum appearance, SpriteBitmapInfo* bitmap, SpriteInfo* sup,
	GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, glm::vec4 tone, GLboolean is_visible,
	GLenum direction, GLenum x_align, GLenum y_align, std::wstring style);

void UpdateFPS_Box(FPS_BoxInfo* fpsbox);

void DestroyFPS_Box(FPS_BoxInfo* fpsbox);

/*-----------------------------------------------------------------------------------------------*/

FPS_BoxInfo* CreateFPS_Box(GLenum appearance, SpriteBitmapInfo* bitmap, SpriteInfo* sup,
	GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, glm::vec4 tone, GLboolean is_visible,
	GLenum direction, GLenum x_align, GLenum y_align, std::wstring style) {
	FPS_BoxInfo* fpsbox = new FPS_BoxInfo;
	fpsbox->text = CreateTextBox(appearance, bitmap, sup, x, y, z, w, h, tone, GL_TRUE,
		style + L"---", direction, x_align, y_align);
	fpsbox->style = style;
	fpsbox->is_visible = is_visible;
	return fpsbox;
};

void UpdateFPS_Box(FPS_BoxInfo* fpsbox) {
	if (fpsbox->is_visible) {
		if (SystemTimer->fps_updated) {
			SetTextBoxText(fpsbox->text, fpsbox->style + std::to_wstring(SystemTimer->fps));
		}
		UpdateTextBox(fpsbox->text);
	}
};

void DestroyFPS_Box(FPS_BoxInfo* fpsbox) {
	DestroyTextBox(fpsbox->text);
	delete fpsbox;
};