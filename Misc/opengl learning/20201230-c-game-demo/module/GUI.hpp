#pragma once

#include "BasicModules.hpp"

/*-----------------------------------------------------------------------------------------------*/
enum GUI_Appearances { GUI_Texture, GUI_Rectangle, GUI_GradBar };
enum GUI_Directions { GUI_Horizontal, GUI_Vertical };
enum GUI_Alignments { GUI_AlignLeft, GUI_AlignCentre, GUI_AlignRight, 
	GUI_AlignTop, GUI_AlignBottom };

const glm::vec4 GUI_Red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 GUI_Green = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
const glm::vec4 GUI_Blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
const glm::vec4 GUI_Black = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 GUI_White = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
const glm::vec4 GUI_Yellow = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
const glm::vec4 GUI_Magenta = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
const glm::vec4 GUI_Cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

const glm::vec4 GUI_TransparentRed = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
const glm::vec4 GUI_TransparentGreen = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
const glm::vec4 GUI_TransparentBlue = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
const glm::vec4 GUI_TransparentBlack = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
const glm::vec4 GUI_TransparentWhite = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);

const GLuint GUI_ColorsNum = 10;
const glm::vec4 GUI_Colors[11] = {
	GameFontColor,		//0
	GUI_Red,			//1
	GUI_Green,			//2
	GUI_Blue,			//3
	GUI_Black,			//4
	GUI_White,			//5
	GUI_Yellow,			//6
	GUI_Magenta,		//7
	GUI_Cyan,			//8
};
/*-----------------------------------------------------------------------------------------------*/
glm::vec4 GUI_GetColor(glm::vec4 color, GLfloat alpha) {
	return glm::vec4(glm::vec3(color), alpha);
}

void GUI_FillRect(GLfloat x, GLfloat y, GLfloat w, GLfloat h, glm::vec4 c, glm::mat4 trans) {
	DrawQuad2D(x, y + h, c, x + w, y + h, c, x + w, y, c, x, y, c, 0.0f, NULL, trans);
}

void GUI_FillBitmap(GLfloat x, GLfloat y, GLfloat w, GLfloat h, glm::vec4 c, 
	SpriteBitmapInfo *bitmap, GLuint index, glm::mat4 trans) {
	Quad2D_Info* quad = CreateShapeQuad2D(
		x, y + h, c, x + w, y + h, c, x + w, y, c, x, y, c, 0.0f,
		Quad2D->vao, Quad2D->vbo, Shape2D->tex_program);
	GLuint x_index = index % bitmap->x_num;
	GLuint y_index = index / bitmap->x_num;
	GLfloat x_delta = 1.0f / bitmap->x_num;
	GLfloat y_delta = 1.0f / bitmap->y_num;
	SetShapeQuad2D_TexCoords(quad,
		x_index * x_delta, (y_index + 1) * y_delta,
		(x_index + 1) * x_delta, (y_index + 1) * y_delta,
		(x_index + 1) * x_delta, y_index * y_delta,
		x_index * x_delta, y_index * y_delta
	);
	DrawShapeQuad2D(quad, bitmap->texture, trans);
	DestroyShapeQuad2D(quad);
}

void GUI_FillGradRect(GLfloat x, GLfloat y, GLfloat w, GLfloat h,
	glm::vec4 c1, glm::vec4 c2, GLenum direction, GLboolean symmetric,
	glm::mat4 trans) {
	switch (direction)
	{
	case GUI_Horizontal:
		if (symmetric) {
			GUI_FillGradRect(x, y, w / 2, h, c1, c2, GUI_Horizontal, GL_FALSE, trans);
			GUI_FillGradRect(x + w / 2, y, w / 2, h, c2, c1, GUI_Horizontal, GL_FALSE, trans);
		}
		else {
			DrawQuad2D(x, y + h, c1, x + w, y + h, c2, x + w, y, c2, x, y, c1, 0.0f, NULL, trans);
		}
		break;
	case GUI_Vertical:
		if (symmetric) {
			GUI_FillGradRect(x, y, w, h / 2, c1, c2, GUI_Vertical, GL_FALSE, trans);
			GUI_FillGradRect(x, y + h / 2, w, h / 2, c2, c1, GUI_Vertical, GL_FALSE, trans);
		}
		else {
			DrawQuad2D(x, y + h, c2, x + w, y + h, c2, x + w, y, c1, x, y, c1, 0.0f, NULL, trans);
		}
		break;
	default:
		break;
	}
}

void GUI_DrawText(GLfloat x, GLfloat y, GLfloat w, GLfloat h, std::wstring text,
	GLenum direction, GLenum x_align, GLenum y_align, glm::mat4 trans) {

	Quad2D_Info** quad = new Quad2D_Info*[text.size()];
	Quad2D_Info** out_quad = new Quad2D_Info*[text.size()];
	CharTexInfo** ctex = new CharTexInfo*[text.size()];
	CharTexInfo** out_ctex = new CharTexInfo*[text.size()];

	std::string fontfile = GetGameFile(GameFontDir, GameFontFile);
	FontInfo * font = GetFont(fontfile);
	GLuint font_index = 0;
	GLuint size = GameFontSize;
	GLuint linewidth = GameFontLineWidth;
	GLuint bolden = GameFontBolden;
	GLuint italic = GameFontItalic;
	GLboolean is_vertical = direction == GUI_Vertical ? GL_TRUE : GL_FALSE;
	glm::vec4 color = GameFontColor;
	GLuint color_index = 0;
	GLboolean is_gradient = GL_FALSE;
	GLuint outline = GameFontOutline;
	glm::vec4 outline_color = GameFontOutlineColor;
	GLuint outline_color_index = 0;

	GLfloat px = x, py = y;
	GLfloat ox = x, oy = y;
	for (GLuint i = 0; i < text.size(); ++i) {
		if (text[i] == L'\\') {
			quad[i] = NULL;
			out_quad[i] = NULL;
			quad[i + 1] = NULL;
			out_quad[i + 1] = NULL;
			switch (text[++i]) {
			case L's': //size
				size = 0;
				while (iswdigit(text[++i])) {
					quad[i] = NULL;
					out_quad[i] = NULL;
					size = size * 10 + text[i] - L'0';
				}
				if (text[--i] == L's') {
					size = GameFontSize;
				}
				break;
			case L'b': //bolden
				bolden = 0;
				while (iswdigit(text[++i])) {
					quad[i] = NULL;
					out_quad[i] = NULL;
					bolden = bolden * 10 + text[i] - L'0';
				}
				if (text[--i] == L'b') {
					bolden = GameFontBolden;
				}
				break;
			case L'i': //italic
				italic = 0;
				while (iswdigit(text[++i])) {
					quad[i] = NULL;
					out_quad[i] = NULL;
					italic = italic * 10 + text[i] - L'0';
				}
				if (text[--i] == L'i') {
					italic = GameFontItalic;
				}
				break;
			case L'l': //line width
				linewidth = 0;
				while (iswdigit(text[++i])) {
					quad[i] = NULL;
					out_quad[i] = NULL;
					linewidth = linewidth * 10 + text[i] - L'0';
				}
				if (text[--i] == L'l') {
					linewidth = GameFontLineWidth;
				}
				break;
			case L'c': //color
				color_index = 0;
				while (iswdigit(text[++i])) {
					quad[i] = NULL;
					out_quad[i] = NULL;
					color_index = color_index * 10 + text[i] - L'0';
				}
				if (text[--i] == L'c' || color_index >= GUI_ColorsNum) {
					color = GameFontColor;
				}
				else {
					color = GUI_Colors[color_index];
				}
				break;
			case L'g': //gradient
				is_gradient = !is_gradient;
				break;
			case L'o': //outline
				outline = 0;
				while (iswdigit(text[++i])) {
					quad[i] = NULL;
					out_quad[i] = NULL;
					outline = outline * 10 + text[i] - L'0';
				}
				if (text[--i] == L'o') {
					outline = GameFontOutline;
				}
				break;
			case L'C': //outline color
				outline_color_index = 0;
				while (iswdigit(text[++i])) {
					quad[i] = NULL;
					out_quad[i] = NULL;
					outline_color_index = outline_color_index * 10 + text[i] - L'0';
				}
				if (text[--i] == L'C' || outline_color_index >= GUI_ColorsNum) {
					outline_color = GameFontOutlineColor;
				}
				else {
					outline_color = GUI_Colors[outline_color_index];
				}
				break;
			case L'n': //new line
				if (is_vertical) {
					px -= linewidth;
					ox = glm::min(ox, px);
					oy = glm::max(oy, py);
					py = y;
				}
				else {
					py += linewidth;
					ox = glm::max(ox, px);
					oy = glm::max(oy, py);
					px = x;
				}
				break;
			default:
				break;
			}
		}
		else {
			//ÂÖÀª
			if (outline) {
				out_ctex[i] = CreateCharTex(text[i], font, size, bolden + outline * 2, italic, is_vertical);
				GLfloat x_temp = px + (is_vertical ? out_ctex[i]->tex->width / -2.0f
					: out_ctex[i]->left);
				GLfloat y_temp = py + (is_vertical ? 0 
					: out_ctex[i]->size - out_ctex[i]->top + outline);
				GLfloat w_temp = 1.0f * out_ctex[i]->tex->width;
				GLfloat h_temp = 1.0f * out_ctex[i]->tex->height;
				out_quad[i] = CreateShapeQuad2D(
					x_temp, y_temp + h_temp, outline_color,
					x_temp + w_temp, y_temp + h_temp, outline_color,
					x_temp + w_temp, y_temp, outline_color,
					x_temp, y_temp, outline_color,
					0.0f, Quad2D->vao, Quad2D->vbo, Shape2D->tex_program
				);
			}
			else {
				out_quad[i] = NULL;
			}
			//±¾Ìå
			ctex[i] = CreateCharTex(text[i], font, size, bolden, italic, is_vertical);
			GLfloat x_temp = px + (is_vertical ? ctex[i]->tex->width / -2.0f
				: ctex[i]->left + outline);
			GLfloat y_temp = py + (is_vertical ? outline
				: ctex[i]->size - ctex[i]->top);
			GLfloat w_temp = 1.0f * ctex[i]->tex->width;
			GLfloat h_temp = 1.0f * ctex[i]->tex->height;
			glm::vec4 c_temp = is_gradient ? GUI_GetColor(0.1f * color, 1.0f) : color;
			quad[i] = CreateShapeQuad2D(
				x_temp, y_temp + h_temp, c_temp,
				x_temp + w_temp, y_temp + h_temp, c_temp,
				x_temp + w_temp, y_temp, color,
				x_temp, y_temp, color,
				0.0f, Quad2D->vao, Quad2D->vbo, Shape2D->tex_program
			);
			if (is_vertical) {
				py += ctex[i]->advance_y >> 6;
			}
			else {
				px += ctex[i]->advance_x >> 6;
			}
		}
	}


	if (is_vertical) {
		ox = x * 2 - px - linewidth / 2.0f;
		oy = glm::max(oy, py);
	}
	else {
		ox = glm::max(ox, px);
		oy = py + linewidth;
	}
	switch (x_align)
	{
	case GUI_AlignLeft:
		ox = 0.0f;
		break;
	case GUI_AlignCentre:
		ox = (w - ox + x) / 2.0f;
		break;
	case GUI_AlignRight:
		ox = w - ox + x;
		break;
	default:
		break;
	}
	switch (y_align)
	{
	case GUI_AlignTop:
		oy = 0.0f;
		break;
	case GUI_AlignCentre:
		oy = (h - oy + y) / 2.0f;
		break;
	case GUI_AlignBottom:
		oy = h - oy + y;
		break;
	default:
		break;
	}
	for (GLuint i = 0; i < text.size(); ++i) {
		if (out_quad[i]) {
			out_quad[i]->positions[0].x += ox;
			out_quad[i]->positions[1].x += ox;
			out_quad[i]->positions[2].x += ox;
			out_quad[i]->positions[3].x += ox;
			out_quad[i]->positions[0].y += oy;
			out_quad[i]->positions[1].y += oy;
			out_quad[i]->positions[2].y += oy;
			out_quad[i]->positions[3].y += oy;
			glNamedBufferSubData(out_quad[i]->vbo,
				offsetof(Quad2D_Info, positions), sizeof(out_quad[i]->positions), out_quad[i]);
			glNamedBufferSubData(out_quad[i]->vbo,
				sizeof(out_quad[i]->positions), sizeof(out_quad[i]->colors), out_quad[i]->colors);
			DrawShapeQuad2D(out_quad[i], out_ctex[i]->tex, trans);
			DestroyShapeQuad2D(out_quad[i]);
			DestroyCharTex(out_ctex[i]);
		}
	}
	for (GLuint i = 0; i < text.size(); ++i) {
		if (quad[i]) {
			quad[i]->positions[0].x += ox;
			quad[i]->positions[1].x += ox;
			quad[i]->positions[2].x += ox;
			quad[i]->positions[3].x += ox;
			quad[i]->positions[0].y += oy;
			quad[i]->positions[1].y += oy;
			quad[i]->positions[2].y += oy;
			quad[i]->positions[3].y += oy;
			glNamedBufferSubData(quad[i]->vbo,
				offsetof(Quad2D_Info, positions), sizeof(quad[i]->positions), quad[i]);
			glNamedBufferSubData(quad[i]->vbo,
				sizeof(quad[i]->positions), sizeof(quad[i]->colors), quad[i]->colors);
			DrawShapeQuad2D(quad[i], ctex[i]->tex, trans);
			DestroyShapeQuad2D(quad[i]);
			DestroyCharTex(ctex[i]);
		}
	}

	delete[] ctex;
	delete[] quad;
	delete[] out_ctex;
	delete[] out_quad;
}