#pragma once
#include "core.hpp"
namespace znd {

	Light::Light() {
	}

	Light::Light(vec3 _ambient, vec3 _diffuse, vec3 _specular) {
		ambient = _ambient;
		diffuse = _diffuse;
		specular = _specular;
	}

	Light::Light(float _ambi, float _diff, float _spec, vec3 _color) {
		ambient = _ambi * _color;
		diffuse = _diff * _color;
		specular = _spec * _color;
	}

	Light::~Light() {
	}

}
