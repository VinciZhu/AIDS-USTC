#pragma once
#include "core.hpp"
namespace znd {

	const uint Color::default_rgbas[16] = {
		0xFFFFFFFF, //W 0
		0x000000FF, //K 1
		0xFF0000FF, //R 2
		0x00FF00FF, //G 3
		0x0000FFFF, //B 4
		0x00FFFFFF, //C 5
		0xFF00FFFF, //M 6
		0xFFFF00FF, //Y 7
		0xFFFFFF00,
		0x00000000,
		0xFF000000,
		0x00FF0000,
		0x0000FF00,
		0x00FFFF00,
		0xFF00FF00,
		0xFFFF0000
	};


	Color::Color() {
	}

	Color::Color(uint _rgba) {
		new(this) vec4(_rgba >> 24 & 0xFF, _rgba >> 16 & 0xFF, _rgba >> 8 & 0xFF, _rgba & 0xFF);
		*this /= 255.0f;
	}

	Color::~Color() {
	}

	Color Color::get(uint _rgba) {
		return Color(_rgba);
	}

	Color Color::get_default(uint _index) {
		return get(default_rgbas[_index]);
	}

}
