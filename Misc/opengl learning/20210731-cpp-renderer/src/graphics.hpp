#pragma once
#include "core.hpp"
namespace znd {

	const string Graphics::default_directory = "rs/graphics/";
	const string Graphics::color_shader_files[2] = {
		"color.vert", "color.frag"
	};
	const string Graphics::texture_shader_files[2] = {
		"color_texture.vert", "color_texture.frag"
	};
	const string Graphics::single_channel_shader_files[2] = {
		"color_texture.vert", "single_channel.frag"
	};
	const vec2 Graphics::tex_coords[4] = {
		vec2(0.0f, 1.0f), vec2(1.0f, 1.0f),
		vec2(1.0f, 0.0f), vec2(0.0f, 0.0f)
	};
	const mat4 Graphics::normal_mat = mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	const mat4 Graphics::reverse_mat = mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	void Graphics::set_size(uint _width, uint _height) {
		graphics.pixel_num = _width * _height;
		graphics.aspect_ratio = 1.0f * _width / _height;
		graphics.RenderCanvas::set_size(_width, _height);
		glDeleteTextures(1, &graphics.rsp_ptr_tex);
		glCreateTextures(GL_TEXTURE_2D, 1, &graphics.rsp_ptr_tex);
		glTextureStorage2D(graphics.rsp_ptr_tex, 1, GL_R32F, _width, _height);
		glTextureParameteri(graphics.rsp_ptr_tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(graphics.rsp_ptr_tex, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTextureParameteri(graphics.rsp_ptr_tex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(graphics.rsp_ptr_tex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glNamedFramebufferTexture(graphics.fbo, GL_COLOR_ATTACHMENT1, graphics.rsp_ptr_tex, 0);
	}

	void Graphics::refresh() {
		graphics.set_canvas(graphics);
		graphics.set_renderer(graphics.default_renderer);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		graphics.clear();
		graphics.set_draw_mode(Draw::reverse);
		graphics.draw(Square(-1.0f, -1.0f, 2.0f), graphics);
		glfwSwapBuffers(app.handle);
		glBindFramebuffer(GL_FRAMEBUFFER, graphics.fbo);
	}

	void Graphics::clear(bool _depth_flag, bool _stencil_flag) {
		glClearBufferfv(GL_COLOR, 0, value_ptr(graphics.canvas->clear_color));
		if (_depth_flag) {
			glClear(GL_DEPTH_BUFFER_BIT);
		}
		if (_stencil_flag) {
			glClear(GL_STENCIL_BUFFER_BIT);
		}
	}

	void Graphics::set_draw_mode(uint _mode) {
		graphics.draw_mode = _mode;
		switch (_mode) {
		case Draw::normal:
			graphics.draw_mat = const_cast<mat4*>(&graphics.reverse_mat);
			break;
		case Draw::reverse:
			graphics.draw_mat = const_cast<mat4*>(&graphics.normal_mat);
			break;
		case Draw::pixel:
			graphics.draw_mat = &graphics.canvas->trans_mat;
			break;
		default:
			break;
		}
		graphics.color_program.uniform_mat4("PosMat", *graphics.draw_mat);
		graphics.texture_program.uniform_mat4("PosMat", *graphics.draw_mat);
		graphics.single_channel_program.uniform_mat4("PosMat", *graphics.draw_mat);
	}

	void Graphics::set_draw_program(const Program& _program) {
		graphics.prev_draw_program = graphics.draw_program;
		graphics.draw_program = const_cast<Program*>(&_program);
	}

	void Graphics::reset_draw_program() {
		if (graphics.prev_draw_program) {
			graphics.set_draw_program(*graphics.prev_draw_program);
		}
	}

	void Graphics::set_canvas(const Canvas& _canvas) {
		graphics.prev_canvas = graphics.canvas;
		if (graphics.canvas != &_canvas) {
			glBindFramebuffer(GL_FRAMEBUFFER, _canvas.fbo);
			glViewport(0, 0, _canvas.width, _canvas.height);
			graphics.canvas = const_cast<Canvas*>(&_canvas);
		}
	}

	void Graphics::reset_canvas() {
		if (graphics.prev_canvas) {
			graphics.set_canvas(*graphics.prev_canvas);
		}
	}

	void Graphics::set_renderer(const Renderer& _renderer) {
		graphics.prev_renderer = graphics.renderer;
		if (graphics.renderer) {
			graphics.renderer->end();
		}
		if (graphics.renderer != &_renderer) {
			graphics.renderer = const_cast<Renderer*>(&_renderer);
			graphics.renderer->begin();
		}
	}

	void Graphics::reset_renderer() {
		if (graphics.prev_renderer) {
			graphics.set_renderer(*graphics.prev_renderer);
		}
	}

	uint Graphics::create_quad_vao(uint _vbo, uint _ebo) {
		uint vao;
		glCreateVertexArrays(1, &vao);
		glEnableVertexArrayAttrib(vao, 0);
		glEnableVertexArrayAttrib(vao, 1);
		glEnableVertexArrayAttrib(vao, 2);
		glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribFormat(vao, 1, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayVertexBuffer(vao, 0, _vbo, 0, 12);
		glVertexArrayVertexBuffer(vao, 1, _vbo, 48, 16);
		glVertexArrayVertexBuffer(vao, 2, _vbo, 112, 8);
		glVertexArrayAttribBinding(vao, 0, 0);
		glVertexArrayAttribBinding(vao, 1, 1);
		glVertexArrayAttribBinding(vao, 2, 2);
		glVertexArrayElementBuffer(vao, _ebo);
		return vao;
	}

	uint Graphics::create_quad_vbo() {
		uint vbo;
		glCreateBuffers(1, &vbo);
		glNamedBufferStorage(vbo, 144, NULL, GL_DYNAMIC_STORAGE_BIT);
		glNamedBufferSubData(vbo, 112, 32, graphics.tex_coords);
		return vbo;
	}

	uint Graphics::create_quad_ebo() {
		uint ebo;
		uint indices[6] = { 0, 1, 2, 2, 3, 0 };
		glCreateBuffers(1, &ebo);
		glNamedBufferData(ebo, 24, indices, GL_STATIC_DRAW);
		return ebo;
	}

	void Graphics::draw(const Quad& _quad) {
		draw(_quad, *graphics.draw_program);
	}

	void Graphics::draw(const Quad& _quad, const Program& _program) {
		const_cast<Program*>(&_program)->use();
		glBindVertexArray(graphics.quad_vao);
		glNamedBufferSubData(graphics.quad_vbo, 0, 48, _quad.coords);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Graphics::draw(const Quad& _quad, const vec4& _c) {
		draw(_quad, _c, _c, _c, _c);
	}

	void Graphics::draw(const Quad& _quad, const Bitmap& _bitmap, const vec4& _c) {
		draw(_quad, Texture(_bitmap), _c, _bitmap.channel_num == 1);
	}

	void Graphics::draw(const Quad& _quad, const Texture& _tex, const vec4& _c, bool _is_single_channel) {
		draw(_quad, _tex, _c, _c, _c, _c, _is_single_channel);
	}

	void Graphics::draw(const Quad& _quad, const vec4& _c0, const vec4& _c1, const vec4& _c2, const vec4& _c3) {
		glNamedBufferSubData(graphics.quad_vbo, 48, 16, &_c0);
		glNamedBufferSubData(graphics.quad_vbo, 64, 16, &_c1);
		glNamedBufferSubData(graphics.quad_vbo, 80, 16, &_c2);
		glNamedBufferSubData(graphics.quad_vbo, 96, 16, &_c3);
		draw(_quad, graphics.color_program);
	}

	void Graphics::draw(const Quad& _quad, const Texture& _tex,
		const vec4& _c0, const vec4& _c1, const vec4& _c2, const vec4& _c3, bool _is_single_channel) {
		glBindTextureUnit(0, _tex.name);
		glNamedBufferSubData(graphics.quad_vbo, 48, 16, &_c0);
		glNamedBufferSubData(graphics.quad_vbo, 64, 16, &_c1);
		glNamedBufferSubData(graphics.quad_vbo, 80, 16, &_c2);
		glNamedBufferSubData(graphics.quad_vbo, 96, 16, &_c3);
		if (_is_single_channel) {
			draw(_quad, graphics.single_channel_program);
		}
		else {
			draw(_quad, graphics.texture_program);
		}

	}

}





