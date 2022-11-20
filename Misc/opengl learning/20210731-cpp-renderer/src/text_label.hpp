#pragma once
#include "core.hpp"
namespace znd {

	const uint TextLabel::font_default_file = 0;
	const uint TextLabel::font_default_color = 0;
	const uint TextLabel::font_default_outline_color = 1;
	const uint TextLabel::font_default_size = 24;
	const uint TextLabel::font_default_linewidth = 32;
	const uint TextLabel::font_default_bolden = 0;
	const uint TextLabel::font_default_italic = 0;
	const uint TextLabel::font_default_outline = 1;

	TextLabel::TextLabel() {
	}

	TextLabel::TextLabel(const vec3& _translation, uint _appearance, const vec4& _color, const Rect& _rect,
		wstring _text, uint _direction, uint _x_align, uint _y_align) :
		DisplayBox(_translation, _appearance, _color, _rect) {
		new(&text_canvas) Canvas((uint)abs(_rect.w), (uint)abs(_rect.h));
		new(&text_sprite) Sprite(vec3(0.0f, 0.0f, 0.1f), &text_canvas, _rect);
		text_sprite.set_super(this);
		text = _text;
		direction = _direction;
		x_align = _x_align;
		y_align = _y_align;
		refresh_text();
	}

	TextLabel::TextLabel(const vec3& _translation, uint _appearance, const Texture* _texture, const Rect& _rect,
		wstring _text, uint _direction, uint _x_align, uint _y_align) :
		DisplayBox(_translation, _appearance, _texture, _rect) {
		new(&text_canvas) Canvas((uint)abs(_rect.w), (uint)abs(_rect.h));
		new(&text_sprite) Sprite(vec3(0.0f, 0.0f, 0.1f), &text_canvas, _rect);
		text_sprite.set_super(this);
		text = _text;
		direction = _direction;
		x_align = _x_align;
		y_align = _y_align;
		refresh_text();
	}

	TextLabel::~TextLabel() {
	}

	void TextLabel::refresh_text() {
		Font& font = Font::get_default(font_default_file);
		uint font_color = font_default_color;
		uint outline_color = font_default_outline_color;
		uint file = font_default_file;
		uint size = font_default_size;
		uint linewidth = font_default_linewidth;
		uint bolden = font_default_bolden;
		uint italic = font_default_italic;
		uint outline = font_default_outline;
		bool vertical_flag = direction == Direction::vertical ? true : false;
		bool gradient_flag = false;
		float w = 1.0f * text_canvas.width;
		float h = 1.0f * text_canvas.height;
		float px = vertical_flag ? w - linewidth / 2 : 0.0f, py = 0.0f;
		float ox = vertical_flag ? w - linewidth / 2 : 0.0f, oy = 0.0f;
		graphics.set_canvas(text_canvas);
		graphics.set_draw_mode(Draw::pixel);
		graphics.clear();
		for (uint i = 0; i < text.size(); ++i) {
			if (text[i] == L'\\') {
				switch (text[++i]) {
				case L's': //size
					size = 0;
					while (iswdigit(text[++i])) {
						size = size * 10 + text[i] - L'0';
					}
					if (text[--i] == L's') {
						size = font_default_size;
					}
					break;
				case L'b': //bolden
					bolden = 0;
					while (iswdigit(text[++i])) {
						bolden = bolden * 10 + text[i] - L'0';
					}
					if (text[--i] == L'b') {
						bolden = font_default_bolden;
					}
					break;
				case L'i': //italic
					italic = 0;
					while (iswdigit(text[++i])) {
						italic = italic * 10 + text[i] - L'0';
					}
					if (text[--i] == L'i') {
						italic = font_default_italic;
					}
					break;
				case L'l': //line width
					linewidth = 0;
					while (iswdigit(text[++i])) {
						linewidth = linewidth * 10 + text[i] - L'0';
					}
					if (text[--i] == L'l') {
						linewidth = font_default_linewidth;
					}
					break;
				case L'c': //color
					font_color = 0;
					while (iswdigit(text[++i])) {
						font_color = font_color * 10 + text[i] - L'0';
					}
					if (text[--i] == L'c' || font_color >= 16) {
						font_color = font_default_color;
					}
					break;
				case L'g': //gradient
					gradient_flag = !gradient_flag;
					break;
				case L'o': //outline
					outline = 0;
					while (iswdigit(text[++i])) {
						outline = outline * 10 + text[i] - L'0';
					}
					if (text[--i] == L'o') {
						outline = font_default_outline;
					}
					break;
				case L'C': //outline color
					outline_color = 0;
					while (iswdigit(text[++i])) {
						outline_color = outline_color * 10 + text[i] - L'0';
					}
					if (text[--i] == L'C' || outline_color >= 16) {
						outline_color = font_default_outline_color;
					}
					break;
				case L'n': //new line
					if (vertical_flag) {
						px -= linewidth;
						ox = glm::min(ox, px);
						oy = glm::max(oy, py);
						py = 0.0f;
					}
					else {
						py += linewidth;
						ox = glm::max(ox, px);
						oy = glm::max(oy, py);
						px = 0.0f;
					}
					break;
				default:
					break;
				}
			}
			else {
				if (outline) {
					Character out_character(text[i], font, size, bolden + outline * 2, italic, vertical_flag);
					float x_temp = px + (vertical_flag ? out_character.width / -2.0f : out_character.left);
					float y_temp = py + (vertical_flag ? 0 : out_character.size - out_character.top + outline);
					float w_temp = 1.0f * out_character.width;
					float h_temp = 1.0f * out_character.rows;
					graphics.draw(Rect(x_temp, y_temp + h_temp, w_temp, -h_temp), out_character,
						Color::get_default(outline_color), true);
				}
				Character& character = Character::get(text[i], font, size, bolden, italic, vertical_flag);
				float x_temp = px + (vertical_flag ? character.width / -2.0f : character.left + outline);
				float y_temp = py + (vertical_flag ? outline : character.size - character.top);
				float w_temp = 1.0f * character.width;
				float h_temp = 1.0f * character.rows;
				vec4 c1_temp = Color::get_default(font_color);
				vec4 c2_temp = gradient_flag ? vec4(0.1f * vec3(c1_temp), c1_temp.a) : c1_temp;
				graphics.draw(Rect(x_temp, y_temp + h_temp, w_temp, -h_temp), character,
					c1_temp, c1_temp, c2_temp, c2_temp, true);
				if (vertical_flag) {
					py += character.advance_y >> 6;
				}
				else {
					px += character.advance_x >> 6;
				}
			}
		}
		graphics.reset_canvas();
		if (vertical_flag) {
			ox = glm::min(ox, px) - linewidth / 2.0f;
			oy = glm::max(oy, py);
		}
		else {
			ox = glm::max(ox, px);
			oy = glm::max(oy, py) + linewidth;
		}
		switch (x_align)
		{
		case Align::left:
			text_sprite.translation.x = vertical_flag ? -ox : 0.0f;
			break;
		case Align::center:
			text_sprite.translation.x = vertical_flag ? -ox / 2.0f : (w - ox) / 2.0f;
			break;
		case Align::right:
			text_sprite.translation.x = vertical_flag ? 0.0f : w - ox;
			break;
		default:
			break;
		}
		switch (y_align)
		{
		case Align::top:
			text_sprite.translation.y = 0.0f;
			break;
		case Align::center:
			text_sprite.translation.y = (h - oy) / 2.0f;
			break;
		case Align::bottom:
			text_sprite.translation.y = h - oy;
			break;
		default:
			break;
		}
	}


	void TextLabel::update() {
		Sprite::update();
		text_sprite.update();
	}

	void TextLabel::render() {
		if (visible_flag) {
			Sprite::render();
			text_sprite.render();
		}
	}

	void TextLabel::set_text(wstring _text) {
		text = _text;
		refresh_text();
	}

	void TextLabel::set_direction(uint _direction) {
		direction = _direction;
		refresh_text();
	}

	void TextLabel::set_x_align(uint _x_align) {
		x_align = _x_align;
		refresh_text();
	}

	void TextLabel::set_y_align(uint _y_align) {
		y_align = _y_align;
		refresh_text();
	}

}
