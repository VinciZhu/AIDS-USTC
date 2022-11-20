#pragma once
#include "core.hpp"
namespace znd {

	

	Character::Character() {
	}

	Character::Character(wchar_t _ch, const Font& _font, uint _size,
		uint _bolden, uint _italic, bool _is_vertical) {
		if (FT_Set_Pixel_Sizes(_font.face, _size, _size)) {
			cerr << "[Znd] Error: failed to set font size" << endl;
		}
		if (FT_Load_Char(_font.face, _ch, FT_LOAD_NO_BITMAP |
			(_is_vertical ? FT_LOAD_VERTICAL_LAYOUT : 0))) {
			cerr << "[Znd] Error: failed to load glyph" << endl;
		}
		FT_Outline_Embolden(&_font.face->glyph->outline, _bolden << 6);
		FT_Matrix matrix;
		matrix.xx = 1 << 16; matrix.xy = (_italic << 16) / _size;
		matrix.yx = 0; matrix.yy = 1 << 16;
		FT_Outline_Transform(&_font.face->glyph->outline, &matrix);
		FT_Render_Glyph(_font.face->glyph, FT_RENDER_MODE_NORMAL);
		new(this) Texture(Bitmap(_font.face->glyph->bitmap.width, _font.face->glyph->bitmap.rows, 1,
			_font.face->glyph->bitmap.buffer), Texture::common);
		size = _size;
		bolden = _bolden;
		italic = _italic;
		is_vertical = _is_vertical;
		left = _font.face->glyph->bitmap_left;
		top = _font.face->glyph->bitmap_top;
		width = _font.face->glyph->bitmap.width;
		rows = _font.face->glyph->bitmap.rows;
		advance_x = _font.face->glyph->advance.x;
		advance_y = _font.face->glyph->advance.y;
	}

	Character::~Character() {
	}

	Character& Character::get(wchar_t _ch, const string& _filename, uint _size,
		uint _bolden, uint _italic, bool _is_vertical) {
		Font& font = Font::get(_filename);
		auto itr = font.char_cache.find(_ch);
		if (itr == font.char_cache.end()) {
			return *(font.char_cache[_ch] = new Character(_ch, font, _size, _bolden, _italic, _is_vertical));
		}
		else {
			if (itr->second->bolden != _bolden ||
				itr->second->italic != _italic ||
				itr->second->is_vertical != _is_vertical ||
				itr->second->size < _size) {
				delete itr->second;
				itr->second = new Character(_ch, font, _size, _bolden, _italic, _is_vertical);
			}
			return *itr->second;
		}
	}

	Character& Character::get(wchar_t _ch, const Font& _font, uint _size,
		uint _bolden, uint _italic, bool _is_vertical) {
		Font& font = *const_cast<Font*>(&_font);
		auto itr = font.char_cache.find(_ch);
		if (itr == font.char_cache.end()) {
			return *(font.char_cache[_ch] = new Character(_ch, font, _size, _bolden, _italic, _is_vertical));
		}
		else {
			if (itr->second->bolden != _bolden ||
				itr->second->italic != _italic ||
				itr->second->is_vertical != _is_vertical ||
				itr->second->size != _size) {
				delete itr->second;
				itr->second = new Character(_ch, font, _size, _bolden, _italic, _is_vertical);
			}
			return *itr->second;
		}
	}

}
