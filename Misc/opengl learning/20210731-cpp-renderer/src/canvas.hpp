#pragma once
#include "core.hpp"
namespace znd {

	Canvas::Canvas() {
	}

	Canvas::Canvas(uint _width, uint _height, const vec4& _clear_color) {
		clear_color = _clear_color;
		type = common;
		glCreateFramebuffers(1, &fbo);
		set_size(_width, _height);
	}

	Canvas::~Canvas() {
		glDeleteFramebuffers(1, &fbo);
	}

	void Canvas::set_size(uint _width, uint _height) {
		width = _width;
		height = _height;
		trans_mat = ortho(0.0f, 1.0f * _width, 0.0f, 1.0f * _height);
		glDeleteTextures(1, &name);
		glCreateTextures(GL_TEXTURE_2D, 1, &name);
		glTextureStorage2D(name, 1, GL_RGBA8, _width, _height);
		glTextureParameteri(name, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(name, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTextureParameteri(name, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(name, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glNamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0, name, 0);
	}

}
