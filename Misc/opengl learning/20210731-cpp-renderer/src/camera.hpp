#pragma once
#include "core.hpp"
namespace znd {

	Camera::Camera() {
	}

	Camera::Camera(const vec3& _position, const vec3& _center, float _fov, float _near, float _far) {
		fov = _fov;
		near = _near;
		far = _far;
		position = _position;
		center = _center;
		update_trans_mat();
	}

	Camera::~Camera() {
	}

	void Camera::set_position(const vec3& _position) {
		position = _position;
		update_trans_mat();
	}

	void Camera::set_center(const vec3& _center) {
		center = _center;
		update_trans_mat();
	}

	void Camera::update_trans_mat() {
		trans_mat = perspective(fov, graphics.aspect_ratio, near, far)
			* lookAt(position, center, vec3(0.0f, 1.0f, 0.0f));
	}

}
