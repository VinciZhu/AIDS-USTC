#pragma once
#include "core.hpp"
namespace znd {

	CommandButton::CommandButton() {
	}

	CommandButton::CommandButton(
		const vec3& _translation, uint _appearance, const vec4& _color, const Rect& _rect,
		wstring _text, uint _direction, uint _x_align, uint _y_align
	) :
		TextLabel(_translation, _appearance, _color, _rect, _text, _direction, _x_align, _y_align) {
		new(&responder) EventResponder(nullptr);
		rsp_ptr = &responder;
		text_sprite.rsp_ptr = &responder;
	}

	CommandButton::CommandButton(
		const vec3& _translation, uint _appearance, const Texture* _texture, const Rect& _rect,
		wstring _text, uint _direction, uint _x_align, uint _y_align
	) :
		TextLabel(_translation, _appearance, _texture, _rect, _text, _direction, _x_align, _y_align) {
		new(&responder) EventResponder(nullptr);
		rsp_ptr = &responder;
		text_sprite.rsp_ptr = &responder;
	}

	CommandButton::~CommandButton() {
	}

	void CommandButton::update() {
		Sprite::update();
		text_sprite.update();
	}
}
