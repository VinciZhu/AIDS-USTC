#pragma once
#include "core.hpp"
namespace znd {

	void Application::default_key_callback(Handle _handle, int _key, int _scancode, int _action, int _mode) {

	}

	void Application::default_windowsize_callback(Handle _handle, int _width, int _height) {
		graphics.set_size(_width, _height);
		graphics.oit.update();
		graphics.render_3d.update();
	}

	void Application::default_cursorpos_callback(Handle _handle, double _xpos, double _ypos) {
	}

	void Application::default_mousebutton_callback(Handle _handle, int _button, int _action, int _mods) {
		if (_button == GLFW_MOUSE_BUTTON_LEFT) {
			if (_action == GLFW_PRESS) {
				if (app.cur_responder) {
				app.cur_responder->down();
				}
			}
			else if (_action == GLFW_RELEASE) {
				if (app.cur_responder) {
					app.cur_responder->up();
				}
			}
		}
	}

	void Application::default_scroll_callback(Handle _handle, double _xoffset, double _yoffset) {
	}

	void Application::error_callback(int error, const char* description)
	{
		cout << "[Znd] Error: " << description << endl;
	}

	void Application::init(const string& _title, uint _width, uint _height) {
		if (!glfwInit()) {
			cerr << "[Znd] Error: failed to initialize glfw" << endl;
		}
		app.handle = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
		if (!app.handle) {
			cerr << "[Znd] Error: failed to create app" << endl;
		}
		glfwMakeContextCurrent(app.handle);
		glfwSetErrorCallback(error_callback);
		glfwSwapInterval(0);
		set_key_callback(default_key_callback);
		set_windowsize_callback(default_windowsize_callback);
		set_cursorpos_callback(default_cursorpos_callback);
		set_mousebutton_callback(default_mousebutton_callback);
		set_scroll_callback(default_scroll_callback);
		if (!gladLoadGL(glfwGetProcAddress)) {
			cerr << "[Znd] Error: failed to load opengl" << endl;
		}
		app.exit_flag = false;
		app.title = _title;
		app.cur_time = glfwGetTime();
		app.prev_time = glfwGetTime();
		glfwGetCursorPos(app.handle, &app.cursor_x, &app.cursor_y);
		app.cur_responder = nullptr;
		app.prev_responder = nullptr;
		app.frame_cnt = 0;
		app.fps = 0;
		srand((uint)time(NULL));

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
		graphics.clear_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		graphics.trans_mat = mat4(1.0f);
		graphics.type = Texture::common;
		glCreateFramebuffers(1, &graphics.fbo);
		uint draw_bufs[] = {
			GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1
		};
		glNamedFramebufferDrawBuffers(graphics.fbo, 2, draw_bufs);
		glNamedFramebufferReadBuffer(graphics.fbo, GL_COLOR_ATTACHMENT1);
		graphics.set_size(_width, _height);
		uint shader_types[] = {
			Shader::vertex, Shader::fragment
		};
		new(&graphics.color_program) Program(2, graphics.color_shader_files, shader_types);
		new(&graphics.texture_program) Program(2, graphics.texture_shader_files, shader_types);
		new(&graphics.single_channel_program) Program(2, graphics.single_channel_shader_files, shader_types);
		graphics.quad_ebo = graphics.create_quad_ebo();
		graphics.quad_vbo = graphics.create_quad_vbo();
		graphics.quad_vao = graphics.create_quad_vao(graphics.quad_vbo, graphics.quad_ebo);
		graphics.set_draw_mode(Draw::normal);
		graphics.set_draw_program(graphics.color_program);
		graphics.set_canvas(graphics);
		graphics.set_renderer(graphics.default_renderer);


		Model::init();
		Font::init();
		TwoD_Renderer::init();
		OIT_Renderer::init();

	}

	void Application::done() {
		Font::done();

		//cache....

		glDeleteTextures(1, &graphics.rsp_ptr_tex);
		glDeleteBuffers(1, &graphics.quad_ebo);
		glDeleteBuffers(1, &graphics.quad_vbo);
		glDeleteVertexArrays(1, &graphics.quad_vao);

		glfwDestroyWindow(app.handle);
		glfwTerminate();
	}

	void Application::update() {
		graphics.refresh();

		app.process_events();

		app.cur_time= glfwGetTime();
		++app.frame_cnt;
		if (app.cur_time - app.prev_time >= 1) {
			app.prev_time = app.cur_time;
			app.fps = app.frame_cnt;
			app.frame_cnt = 0;
		}

		app.prev_responder = app.cur_responder;
		glfwGetCursorPos(app.handle, &app.cursor_x, &app.cursor_y);
		glReadPixels((int)app.cursor_x, (int)app.cursor_y, 1, 1, GL_RED, GL_FLOAT, &app.cur_responder);
		if (app.cur_responder != app.prev_responder) {
			if (app.cur_responder) {
				app.cur_responder->in();
			}
			if (app.prev_responder) {
				app.prev_responder->out();
			}
		}
		if (glfwWindowShouldClose(app.handle)) {
			app.exit_flag = true;
		};

		graphics.clear();
		float temp = 0.0f;
		glClearBufferfv(GL_COLOR, 1, &temp);
	}

	void Application::process_events() {
		glfwPollEvents();
	}

	void Application::set_key_callback(KeyFun _callback) {
		glfwSetKeyCallback(app.handle, _callback);
	}

	void Application::set_windowsize_callback(WindowsizeFun _callback) {
		glfwSetWindowSizeCallback(app.handle, _callback);
	}

	void Application::set_cursorpos_callback(CursorposFun _callback) {
		glfwSetCursorPosCallback(app.handle, _callback);
	}

	void Application::set_mousebutton_callback(MousebuttonFun _callback) {
		glfwSetMouseButtonCallback(app.handle, _callback);
	}

	void Application::set_scroll_callback(ScrollFun _callback) {
		glfwSetScrollCallback(app.handle, _callback);
	}
}





