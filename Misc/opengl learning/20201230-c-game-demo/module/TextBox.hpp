#pragma once

#include "GUI.hpp"

/*-----------------------------------------------------------------------------------------------*/
typedef struct _TextBoxInfo {
	GLenum appearance;
	SpriteInfo* sprite;
	GLboolean is_visible;
	std::wstring text;
	GLenum direction;
	GLenum y_align;
	GLenum x_align;
	SpriteInfo* text_sprite;
}TextBoxInfo;


TextBoxInfo* CreateTextBox(GLenum appearance, SpriteBitmapInfo* bitmap, SpriteInfo* sup,
	GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, glm::vec4 tone, GLboolean is_visible,
	std::wstring text, GLenum direction, GLenum x_align, GLenum y_align);

void UpdateTextBox(TextBoxInfo* textbox);

void RefreshTextBox(TextBoxInfo* textbox);

void DestroyTextBox(TextBoxInfo* textbox);

void SetTextBoxText(TextBoxInfo* textbox, std::wstring text);

/*-----------------------------------------------------------------------------------------------*/

TextBoxInfo* CreateTextBox(GLenum appearance, SpriteBitmapInfo* bitmap, SpriteInfo* sup, 
	GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, glm::vec4 tone, GLboolean is_visible,
	std::wstring text, GLenum direction, GLenum x_align, GLenum y_align) {
	if (!bitmap) {
		bitmap = CreateDrawBitmap((GLuint)w, (GLuint)h, 1, 1, 4);
	}
	switch (appearance)
	{
	case GUI_Texture:
		break;
	case GUI_Rectangle:
		BeginBitmapDraw(bitmap);
		GUI_FillRect(
			0.0f, 0.0f,
			w, h,
			tone, BitmapDraw->ortho_mat
		);
		EndBitmapDraw(bitmap);
		break;
	case GUI_GradBar:
		BeginBitmapDraw(bitmap);
		GUI_FillGradRect(
			0.0f, 0.0f,
			0.1f * w, h,
			GUI_GetColor(tone, 0.0f), GUI_GetColor(tone, 0.6f),
			GUI_Horizontal, GL_FALSE,
			BitmapDraw->ortho_mat
		);
		GUI_FillGradRect(
			0.1f * w, 0.0f,
			0.8f * w, h,
			glm::vec4(glm::vec3(tone), 0.6f), glm::vec4(glm::vec3(tone), 0.8f),
			GUI_Horizontal, GL_TRUE,
			BitmapDraw->ortho_mat
		);
		GUI_FillGradRect(
			0.9f * w, 0.0f,
			0.1f * w, h,
			GUI_GetColor(tone, 0.6f), GUI_GetColor(tone, 0.0f),
			GUI_Horizontal, GL_FALSE,
			BitmapDraw->ortho_mat
		);
		EndBitmapDraw(bitmap);
		break;
	default:
		break;
	}

	SpriteBitmapInfo* text_bitmap = CreateDrawBitmap((GLuint)w, (GLuint)h, 1, 1, 4);

	TextBoxInfo* textbox = new TextBoxInfo;
	textbox->appearance = appearance;
	textbox->sprite = CreateSprite(sup, bitmap, 0, x, y, z, w, h, 0.0f, tone, GL_TRUE);
	textbox->is_visible = is_visible;
	textbox->direction = direction;
	textbox->y_align = y_align;
	textbox->x_align = x_align;
	textbox->text = text;
	textbox->text_sprite = CreateSprite(textbox->sprite, text_bitmap, 0, 0.0f, 0.0f,
		0.1f, w, h, 0.0f, glm::vec4(1.0f), GL_TRUE);
	RefreshTextBox(textbox);
	return textbox;
}


void UpdateTextBox(TextBoxInfo* textbox) {
	if (textbox->is_visible) {
		UpdateSprite(textbox->sprite);
		UpdateSprite(textbox->text_sprite);
	}
}

void RefreshTextBox(TextBoxInfo* textbox) {
	BeginBitmapDraw(textbox->text_sprite->bitmap);
	GUI_DrawText(0.0f, 0.0f, textbox->text_sprite->w, textbox->text_sprite->h, textbox->text,
		textbox->direction, textbox->x_align, textbox->y_align, BitmapDraw->ortho_mat);
	EndBitmapDraw(textbox->text_sprite->bitmap);
}

void DestroyTextBox(TextBoxInfo* textbox) {
	DestroyDrawBitmap(textbox->text_sprite->bitmap);
	if (textbox->appearance != GUI_Texture) {
		DestroyDrawBitmap(textbox->sprite->bitmap);
	}
	DestroySprite(textbox->sprite);
	delete textbox;
}

void SetTextBoxText(TextBoxInfo* textbox, std::wstring text) {
	textbox->text = text;
	RefreshTextBox(textbox);
}
