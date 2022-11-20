#pragma once
#include "core.hpp"
namespace znd {

	RenderCanvas::RenderCanvas() {
	}

	RenderCanvas::RenderCanvas(uint _width, uint _height, const vec4& _clear_color, bool _stencil_flag) {
		clear_color = _clear_color;
		type = common;
		glCreateFramebuffers(1, &fbo);
		set_size(_width, _height);
	}

	RenderCanvas::~RenderCanvas() {
		glDeleteFramebuffers(1, &rbo);
	}

	void RenderCanvas::set_size(uint _width, uint _height) {
		Canvas::set_size(_width, _height);
		glDeleteRenderbuffers(1, &rbo);
		glCreateRenderbuffers(1, &rbo);
		if (stencil_flag) {
			glNamedRenderbufferStorage(rbo, GL_DEPTH_STENCIL, _width, _height);
			glNamedFramebufferRenderbuffer(fbo, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
		}
		else {
			glNamedRenderbufferStorage(rbo, GL_DEPTH_COMPONENT, _width, _height);
			glNamedFramebufferRenderbuffer(fbo, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
		}
	}

}
