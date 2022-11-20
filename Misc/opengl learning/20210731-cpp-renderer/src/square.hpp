#pragma once
#include "core.hpp"
namespace znd {

	Square::Square() {
	}

	Square::Square(const vec3& _xyz0, float _l) {
		coords[3] = coords[2] = coords[1] = coords[0] = _xyz0;
		coords[1].x += _l;
		coords[2].x += _l;
		coords[2].y += _l;
		coords[3].y += _l;
		w = h = l = _l;
	}

	Square::Square(const vec2& _xy0, float _l, float _z) {
		coords[3] = coords[2] = coords[1] = coords[0] = vec3(_xy0, _z);
		coords[1].x += _l;
		coords[2].x += _l;
		coords[2].y += _l;
		coords[3].y += _l;
		w = h = l = _l;
	}

	Square::Square(float _x0, float _y0, float _l, float _z) {
		coords[0] = vec3(_x0, _y0, _z);
		coords[1] = vec3(_x0 + _l, _y0, _z);
		coords[2] = vec3(_x0 + _l, _y0 + _l, _z);
		coords[3] = vec3(_x0, _y0 + _l, _z);
		w = h = l = _l;
	}

	Square::~Square() {
	}

}
