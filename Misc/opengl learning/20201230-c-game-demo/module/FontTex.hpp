#pragma once

#include "TextureDraw.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_STROKER_H

/*-----------------------------------------------------------------------------------------------*/

struct _FontLib;
struct _FontInfo;
struct _CharTexInfo;

struct _FontLib {
	FT_Library lib;
	std::map<std::string, struct _FontInfo*> fonts;
} * FontLib;

typedef struct _FontInfo {
	FT_Face face;
	std::string filename;
	std::map<wchar_t, struct _CharTexInfo*> chars;
}FontInfo;

typedef struct _CharTexInfo {
	TexInfo* tex;
	wchar_t ch;
	struct _FontInfo* font;
	FT_UInt size;
	FT_UInt bolden;
	FT_UInt italic;
	FT_Bool is_vertical;
	FT_Int left, top;
	FT_Pos advance_x, advance_y;
}CharTexInfo;


void InitFontLibrary();

void DestroyFontLibrary();

FontInfo* CreateFont(std::string filename);

void DestroyFont(FontInfo* font);

FontInfo* GetFont(std::string filename);

CharTexInfo* CreateCharTex(wchar_t ch, FontInfo* font, FT_UInt size,
	FT_UInt bolden, FT_UInt italic, FT_Bool is_vertical);

void DestroyCharTex(CharTexInfo* texture);

CharTexInfo* GetCharTex(wchar_t ch, std::string filename, FT_UInt size,
	FT_UInt bolden, FT_UInt italic, FT_Bool is_vertical);
/*-----------------------------------------------------------------------------------------------*/

void InitFontLibrary() {
	FontLib = new struct _FontLib;
	if (FT_Init_FreeType(&FontLib->lib)) {
#ifdef _DEBUG
		std::cerr << "Error: failed to init freetype library" << std::endl;
#endif // _DEBUG
	}
}

void DestroyFontLibrary() {
	for (std::map<std::string, FontInfo*>::iterator itr = FontLib->fonts.begin(); 
		itr != FontLib->fonts.end(); ++itr) {
		DestroyFont(itr->second);
	}
	FT_Done_FreeType(FontLib->lib);
	delete FontLib;
}

FontInfo* CreateFont(std::string filename) {
	FT_Face face;
	if (FT_New_Face(FontLib->lib, filename.c_str(), 0, &face)) {
#ifdef _DEBUG
		std::cerr << "Error: failed to load font" << std::endl;
#endif // _DEBUG
	}
	FontInfo* font = new FontInfo;
	font->face = face;
	font->filename = filename;
	return font;
}

void DestroyFont(FontInfo* font) {
	for (std::map<wchar_t, CharTexInfo*>::iterator itr = font->chars.begin();
		itr != font->chars.end(); ++itr) {
		DestroyCharTex(itr->second);
	}
	FT_Done_Face(font->face);
	delete font;
}

FontInfo* GetFont(std::string filename) {
	FontInfo* font;
	std::map<std::string, FontInfo*>::iterator font_itr = FontLib->fonts.find(filename);
	if (font_itr == FontLib->fonts.end()) {
		font = CreateFont(filename);
		FontLib->fonts.insert(std::pair<std::string, FontInfo*>(filename, font));
	}
	else {
		font = font_itr->second;
	}
	return font;
}

CharTexInfo* CreateCharTex(wchar_t ch, FontInfo* font, FT_UInt size,
	FT_UInt bolden, FT_UInt italic, FT_Bool is_vertical) {
	if (FT_Set_Pixel_Sizes(font->face, size, size)) {
#ifdef _DEBUG
		std::cerr << "Error: failed to set font size" << std::endl;
#endif // _DEBUG
	}
	if (FT_Load_Char(font->face, ch, FT_LOAD_NO_BITMAP |
		(is_vertical ? FT_LOAD_VERTICAL_LAYOUT : 0))) {
#ifdef _DEBUG
		std::cerr << "Error: failed to load glyph" << std::endl;
#endif // _DEBUG
	}
	FT_Outline_Embolden(&font->face->glyph->outline, bolden << 6);  
	FT_Matrix matrix;
	matrix.xx = 1 << 16; matrix.xy = (italic << 16) / size;
	matrix.yx = 0; matrix.yy = 1 << 16;
	FT_Outline_Transform(&font->face->glyph->outline, &matrix);
	FT_Render_Glyph(font->face->glyph, FT_RENDER_MODE_NORMAL);

	CharTexInfo* texture = new CharTexInfo;
	texture->tex = CreateTexture(GL_TEXTURE_2D, font->face->glyph->bitmap.buffer,
		font->face->glyph->bitmap.width, font->face->glyph->bitmap.rows, 1);
	texture->ch = ch;
	texture->font = font;
	texture->size = size;
	texture->bolden = bolden;
	texture->italic = italic;
	texture->is_vertical = is_vertical;
	texture->left = font->face->glyph->bitmap_left;
	texture->top = font->face->glyph->bitmap_top;
	texture->advance_x = font->face->glyph->advance.x;
	texture->advance_y = font->face->glyph->advance.y;

	return texture;
}

void DestroyCharTex(CharTexInfo* texture) {
	DestroyTexture(texture->tex);
	delete texture;
}

CharTexInfo* GetCharTex(wchar_t ch, std::string filename, FT_UInt size, 
	FT_UInt bolden, FT_UInt italic, FT_Bool is_vertical) {
	FontInfo* font = GetFont(filename);
	std::map<wchar_t, CharTexInfo*>::iterator char_itr = font->chars.find(ch);
	if (char_itr == font->chars.end()) {
		CharTexInfo* texture = CreateCharTex(ch, font, size, 0, 0, is_vertical);
		font->chars.insert(std::pair<wchar_t, CharTexInfo*>(ch, texture));
		return texture;
	}
	else {
		if (char_itr->second->bolden != bolden ||
			char_itr->second->italic != italic ||
			char_itr->second->is_vertical != is_vertical ||
			char_itr->second->size < size) {
			DestroyCharTex(char_itr->second);
			char_itr->second = CreateCharTex(ch, font, size, bolden, italic, is_vertical);
		}
		return char_itr->second;
	}
}
