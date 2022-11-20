#pragma once
#include "core.hpp"
namespace znd {

	Quad::Quad() {
	}

	Quad::Quad(const vec3& _xyz0, const vec3& _xyz1, const vec3& _xyz2, const vec3& _xyz3) {
		coords[0] = _xyz0;
		coords[1] = _xyz1;
		coords[2] = _xyz2;
		coords[3] = _xyz3;
	}

	Quad::Quad(const vec2& _xy0, const vec2& _xy1, const vec2& _xy2, const vec2& _xy3, float _z) {
		coords[0] = vec3(_xy0, _z);
		coords[1] = vec3(_xy1, _z);
		coords[2] = vec3(_xy2, _z);
		coords[3] = vec3(_xy3, _z);
	}

	Quad::Quad(
		float _x0, float _y0, float _z0, float _x1, float _y1, float _z1,
		float _x2, float _y2, float _z2, float _x3, float _y3, float _z3
	) {
		coords[0] = vec3(_x0, _y0, _z0);
		coords[1] = vec3(_x1, _y1, _z1);
		coords[2] = vec3(_x2, _y2, _z2);
		coords[3] = vec3(_x3, _y3, _z3);
	}

	Quad::Quad(
		float _x0, float _y0, float _x1, float _y1,
		float _x2, float _y2, float _x3, float _y3,
		float _z
	) {
		coords[0] = vec3(_x0, _y0, _z);
		coords[1] = vec3(_x1, _y1, _z);
		coords[2] = vec3(_x2, _y2, _z);
		coords[3] = vec3(_x3, _y3, _z);
	}

	Quad::~Quad() {
	}

	bool Quad::operator==(const Quad& _quad) {
		return coords[0] == _quad.coords[0] && 
			coords[1] == _quad.coords[1] &&
			coords[2] == _quad.coords[2] &&
			coords[3] == _quad.coords[3];
	}

	bool Quad::operator!=(const Quad& _quad) {
		return !operator==(_quad);
	}

}
