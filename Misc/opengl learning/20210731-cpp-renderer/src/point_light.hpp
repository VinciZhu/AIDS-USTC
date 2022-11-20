#pragma once
#include "core.hpp"
namespace znd {

	PointLight::PointLight() {
	}

	PointLight::PointLight(vec3 _position, Light _light, float _quadratic, float _linear, float _constant) {
		position = _position;
		ambient = _light.ambient;
		diffuse = _light.diffuse;
		specular = _light.specular;
		constant = _constant;
		linear = _linear;
		quadratic = _quadratic;
	}

	PointLight::PointLight(vec3 _position, vec3 _ambient, vec3 _diffuse, vec3 _specular,
		float _quadratic, float _linear, float _constant) {
		position = _position;
		ambient = _ambient;
		diffuse = _diffuse;
		specular = _specular;
		constant = _constant;
		linear = _linear;
		quadratic = _quadratic;
	}

	PointLight::PointLight(vec3 _position, float _ambi, float _diff, float _spec, vec3 _color,
		float _quadratic, float _linear, float _constant) {
		position = _position;
		ambient = _ambi * _color;
		diffuse = _diff * _color;
		specular = _spec * _color;
		constant = _constant;
		linear = _linear;
		quadratic = _quadratic;
	}

	PointLight::~PointLight() {
	}

}
