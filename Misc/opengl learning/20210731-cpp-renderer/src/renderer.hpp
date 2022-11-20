#pragma once
#include "core.hpp"
namespace znd {

	Renderer::Renderer() {
	}

	Renderer::~Renderer() {
	}

	void Renderer::update() {
	}

	void Renderer::begin() {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}

	void Renderer::end() {
	}

	void Renderer::render_sprite(const Sprite& _sprite) {
	}

	void Renderer::render_model(const Model& _model) {
	}


}
