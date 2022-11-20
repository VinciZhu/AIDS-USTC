#pragma once
#include "core.hpp"
namespace znd {

	DisplayBox::DisplayBox() {
	}

	DisplayBox::DisplayBox(const vec3& _translation, uint _appearance, const vec4& _color, const Rect& _rect) :
		Sprite(_translation, &canvas, _rect) {
		new(&canvas) Canvas((uint)abs(_rect.w), (uint)abs(_rect.h));
		visible_flag = true;
		set_appearance(_appearance,  _color);
	}

	DisplayBox::DisplayBox(const vec3& _translation, uint _appearance, const Texture* _texture, const Rect& _rect) :
		Sprite(_translation, _texture, _rect) {
		new(&canvas) Canvas((uint)abs(_rect.w), (uint)abs(_rect.h));
		visible_flag = true;
		set_appearance(_appearance, _texture);
	}

	DisplayBox::~DisplayBox() {
	}

	void DisplayBox::render() {
		if (visible_flag) {
			Sprite::render();
		}
	}

	void DisplayBox::set_appearance(uint _appearance, const vec4& _color) {
		appearance = _appearance;
		graphics.set_canvas(canvas);
		graphics.set_draw_mode(Draw::normal);
		graphics.clear();
		vec4 transparent_color(vec3(_color), 0.0f);
		switch (_appearance) {
		case Appearance::color:
			graphics.draw(Square(-1.0f, -1.0f, 2.0f), _color);
			break;
		case Appearance::gradient_h:
			graphics.draw(Rect(-1.0f, -1.0f, 1.0f, 2.0f), transparent_color, _color, _color, transparent_color);
			graphics.draw(Rect(0.0f, -1.0f, 1.0f, 2.0f), _color, transparent_color, transparent_color, _color);
			break;
		case Appearance::gradient_v:
			graphics.draw(Rect(-1.0f, 0.0f, 2.0f, 1.0f), _color, _color, transparent_color, transparent_color);
			graphics.draw(Rect(-1.0f, -1.0f, 2.0f, 1.0f), transparent_color, transparent_color, _color, _color);
			break;
		default:
			break;
		}
		texture = &canvas;
		graphics.reset_canvas();
	}

	void DisplayBox::set_appearance(uint _appearance, const Texture* _texture) {
		appearance = _appearance;
		switch (_appearance) {
		case Appearance::texture:
			texture = const_cast<Texture*>(_texture);
			break;
		default:
			break;
		}

	}

}
