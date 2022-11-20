#pragma once
#include "core.hpp"
namespace znd {

	const string OIT_Renderer::shader_files[2] = {
		"texture.vert",
		"oit_frame.frag"
	};

	const string OIT_Renderer::sprite_shader_files[2] = {
		"texture.vert",
		"oit_sprite.frag"
	};
	Program OIT_Renderer::program;
	Program OIT_Renderer::sprite_program;

	void OIT_Renderer::init() {
		uint shader_types[] = {
			Shader::vertex, Shader::fragment
		};
		new(&program) Program(2, shader_files, shader_types);
		new(&sprite_program) Program(2, sprite_shader_files, shader_types);
		program.uniform_mat4("PosMat", mat4(1.0f));
	}

	OIT_Renderer::OIT_Renderer() {
	}

	OIT_Renderer::OIT_Renderer(const Camera& _camera) {
		glCreateBuffers(1, &frag_buf);
		glCreateBuffers(1, &head_ptr_pbo);
		glCreateBuffers(1, &counter_buf);
		glNamedBufferStorage(counter_buf, 4, NULL, GL_MAP_WRITE_BIT);
		glCreateTextures(GL_TEXTURE_BUFFER, 1, &frag_tex);
		glTextureBuffer(frag_tex, GL_RGBA32UI, frag_buf);
		camera = const_cast<Camera*>(&_camera);
		update();
	}

	OIT_Renderer::~OIT_Renderer() {
		glDeleteBuffers(1, &head_ptr_pbo);
		glDeleteTextures(1, &head_ptr_tex);
		glDeleteBuffers(1, &counter_buf);
		glDeleteTextures(1, &frag_tex);
		glDeleteBuffers(1, &frag_buf);
	}

	void OIT_Renderer::update() {
		uint width = graphics.canvas->width;
		uint height = graphics.canvas->height;
		uint pixel_num = width * height;
		glNamedBufferData(frag_buf, pixel_num * 2 * 16, NULL, GL_DYNAMIC_DRAW);
		glDeleteTextures(1, &head_ptr_tex);
		glCreateTextures(GL_TEXTURE_2D, 1, &head_ptr_tex);
		glTextureStorage2D(head_ptr_tex, 1, GL_R32UI, width, height);
		glTextureParameteri(head_ptr_tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(head_ptr_tex, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTextureParameteri(head_ptr_tex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(head_ptr_tex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glNamedBufferData(head_ptr_pbo, pixel_num * 4, NULL, GL_STATIC_DRAW);
		uint *data = (uint*)glMapNamedBuffer(head_ptr_pbo, GL_WRITE_ONLY);
		memset(data, 0x00, pixel_num * 4);
		glUnmapNamedBuffer(head_ptr_pbo);
		camera->update_trans_mat();
	}

	void OIT_Renderer::begin() {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);


		uint *data = (uint*)glMapNamedBuffer(counter_buf, GL_WRITE_ONLY);
		*data = 0;
		glUnmapNamedBuffer(counter_buf);
		glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, counter_buf);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, head_ptr_pbo);
		glTextureSubImage2D(
			head_ptr_tex, 0, 0, 0,
			graphics.canvas->width, graphics.canvas->height, GL_RED_INTEGER, GL_UNSIGNED_INT, nullptr
		);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
		glBindImageTexture(2, frag_tex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32UI);
		glBindImageTexture(1, head_ptr_tex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI);
	}

	void OIT_Renderer::end() {
		program.use();
		graphics.canvas->bind();
		glDisable(GL_DEPTH_TEST);

		glNamedFramebufferDrawBuffer(graphics.fbo, GL_COLOR_ATTACHMENT0);//

		glNamedBufferSubData(graphics.quad_vbo, 0, 48, Rect(-1.0f, 1.0f, 2.0f, -2.0f).coords);
		glBindVertexArray(graphics.quad_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		uint draw_bufs[] = {
			GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1
		};
		glNamedFramebufferDrawBuffers(graphics.fbo, 2, draw_bufs);//
	}

	void OIT_Renderer::render_sprite(const Sprite& _sprite) {
		sprite_program.use();
		sprite_program.uniform_mat4("PosMat",
			graphics.reverse_mat * camera->trans_mat * _sprite.trans_mat);
		sprite_program.uniform_vec4("Color", _sprite.color);
		sprite_program.uniform_vec4("MixColor", _sprite.mix_color);
		_sprite.texture->bind();
		glBindVertexArray(_sprite.vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void OIT_Renderer::render_model(const Model& _model) {
	}


}
