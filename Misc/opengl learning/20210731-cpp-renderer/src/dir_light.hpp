#pragma once
#include "core.hpp"
namespace znd {

	

	DirLight::DirLight() {
	}

	DirLight::DirLight(vec3 _direction, Light _light) {
		direction = _direction;
		ambient = _light.ambient;
		diffuse = _light.diffuse;
		specular = _light.specular;
	}

	DirLight::DirLight(vec3 _direction, vec3 _ambient, vec3 _diffuse, vec3 _specular) {
		direction = _direction;
		ambient = _ambient;
		diffuse = _diffuse;
		specular = _specular;
	}

	DirLight::DirLight(vec3 _direction, float _ambi, float _diff, float _spec, vec3 _color) {
		direction = _direction;
		ambient = _ambi * _color;
		diffuse = _diff * _color;
		specular = _spec * _color;
	}

	DirLight::~DirLight() {
	}

}
