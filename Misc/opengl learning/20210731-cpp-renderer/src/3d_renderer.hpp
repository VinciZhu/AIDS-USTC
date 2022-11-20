#pragma once
#include "core.hpp"
namespace znd {

	ThreeD_Renderer::ThreeD_Renderer() {
	}

	ThreeD_Renderer::ThreeD_Renderer(const Camera& _camera) {
		camera = const_cast<Camera*>(&_camera);
	}

	ThreeD_Renderer::~ThreeD_Renderer() {
	}

	void ThreeD_Renderer::update() {
		camera->update_trans_mat();
	}

	void ThreeD_Renderer::begin() {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);
	}

	void ThreeD_Renderer::end() {
	}

	void ThreeD_Renderer::render_sprite(const Sprite& _sprite) {
		TwoD_Renderer::sprite_program.use();
		TwoD_Renderer::sprite_program.uniform_mat4("PosMat", graphics.reverse_mat * camera->trans_mat * _sprite.trans_mat);
		float temp;
		memcpy(&temp, &_sprite.rsp_ptr, 4);
		TwoD_Renderer::sprite_program.uniform_float("RspPtr", temp);
		TwoD_Renderer::sprite_program.uniform_vec4("Color", _sprite.color);
		TwoD_Renderer::sprite_program.uniform_vec4("MixColor", _sprite.mix_color);
		_sprite.texture->bind();
		glBindVertexArray(_sprite.vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void ThreeD_Renderer::render_model(const Model& _model) {
	}


}
