#pragma once
#include "core.hpp"
namespace znd {

	const string TwoD_Renderer::sprite_shader_files[2] = {
		"texture.vert",
		"sprite.frag"
	};
	Program TwoD_Renderer::sprite_program;

	void TwoD_Renderer::init() {
		uint shader_types[] = {
			Shader::vertex, Shader::fragment
		};
		new(&sprite_program) Program(2, sprite_shader_files, shader_types);
	}

	TwoD_Renderer::TwoD_Renderer() {
	}

	TwoD_Renderer::~TwoD_Renderer() {
	}

	void TwoD_Renderer::update() {
	}

	void TwoD_Renderer::begin() {
		glDisable(GL_DEPTH_TEST);
		glEnablei(GL_BLEND, 0);
		glDisablei(GL_BLEND, 1);
		glBlendFunci(0, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void TwoD_Renderer::end() {
		sprite_program.use();
		while (!graphics.render_2d.sprites.empty()) {
			Sprite& sprite = *sprites.top();
			sprite_program.uniform_mat4("PosMat", graphics.canvas->trans_mat * sprite.trans_mat);
			float temp;
			memcpy(&temp, &sprite.rsp_ptr, 4);
			sprite_program.uniform_float("RspPtr", temp);
			sprite_program.uniform_vec4("Color", sprite.color);
			sprite_program.uniform_vec4("MixColor", sprite.mix_color);
			sprite.texture->bind();
			glBindVertexArray(sprite.vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			sprites.pop();
		}
	}

	void TwoD_Renderer::render_sprite(const Sprite& _sprite) {
		sprites.push(const_cast<Sprite*>(&_sprite));
	}

	void TwoD_Renderer::render_model(const Model& _model) {
	}


}
