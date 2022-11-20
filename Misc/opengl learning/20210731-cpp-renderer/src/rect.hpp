#pragma once
#include "core.hpp"
namespace znd {

	Rect::Rect() {
	}

	Rect::Rect(const vec3& _xyz0, float _w, float _h) : Quad() {
		coords[3] = coords[2] = coords[1] = coords[0] = _xyz0;
		coords[1].x += _w;
		coords[2].x += _w;
		coords[2].y += _h;
		coords[3].y += _h;
		w = _w;
		h = _h;
	}

	Rect::Rect(const vec2& _xy0, float _w, float _h, float _z) {
		coords[3] = coords[2] = coords[1] = coords[0] = vec3(_xy0, _z);
		coords[1].x += _w;
		coords[2].x += _w;
		coords[2].y += _h;
		coords[3].y += _h;
		w = _w;
		h = _h;
	}

	Rect::Rect(float _x0, float _y0, float _w, float _h, float _z) {
		coords[0] = vec3(_x0, _y0, _z);
		coords[1] = vec3(_x0 + _w, _y0, _z);
		coords[2] = vec3(_x0 + _w, _y0 + _h, _z);
		coords[3] = vec3(_x0, _y0 + _h, _z);
		w = _w;
		h = _h;
	}

	Rect::~Rect() {
	}

}
