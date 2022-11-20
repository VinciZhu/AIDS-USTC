//////////////////////////////////
// hasined 2021.3.13
// OpenGL version 4.6 core profile
//////////////////////////////////

extern "C" {
	_declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

#include "znd.h"
using namespace znd;

bool is_rotate_camera;
float camera_yaw;
float camera_pitch;
float camera_radius;
double temp_cursor_x;
double temp_cursor_y;
Camera camera;
DirLight dir_light;
PointLight point_light;

Sprite *sprites[10];
CommandButton test_button;
Sprite::Animation animation(196, true);

void update_camera() {
	camera.position = camera.center;
	camera.position.x += camera_radius * cos(camera_pitch) * sin(camera_yaw);
	camera.position.y += camera_radius * sin(camera_pitch);
	camera.position.z += camera_radius * cos(camera_pitch) * cos(camera_yaw);
	camera.update_trans_mat();
}

void key_callback(Application::Handle _handle, int _key, int _scancode, int _action, int _mode) {
	app.default_key_callback(_handle, _key, _scancode, _action, _mode);
	if (_action == GLFW_PRESS && _key >= GLFW_KEY_0 && _key <= GLFW_KEY_9) {
		Sprite& sprite = *sprites[_key - GLFW_KEY_0];
		Sprite::Animate::get(sprite, &animation).pause_flag ? sprite.resume(animation) : sprite.pause(animation);
	}
}

void windowsize_callback(Application::Handle _handle, int _width, int _height) {
	app.default_windowsize_callback(_handle, _width, _height);
}

void cursorpos_callback(Application::Handle _handle, double _xpos, double _ypos) {
	app.default_cursorpos_callback(_handle, _xpos, _ypos);
	if (is_rotate_camera) {
		camera_yaw -= (float)(0.003 * (_xpos - temp_cursor_x));
		camera_pitch += (float)(0.003 * (_ypos - temp_cursor_y));
		camera_pitch = clamp(camera_pitch, -1.57f, 1.57f);
		temp_cursor_x = _xpos;
		temp_cursor_y = _ypos;
		update_camera();
	}
}

void mousebutton_callback(Application::Handle _handle, int _button, int _action, int _mods) {
	app.default_mousebutton_callback(_handle, _button, _action, _mods);
	if (_button == GLFW_MOUSE_BUTTON_RIGHT || _button == GLFW_MOUSE_BUTTON_MIDDLE) {
		if (_action == GLFW_PRESS) {
			is_rotate_camera = true;
			glfwGetCursorPos(_handle, &temp_cursor_x, &temp_cursor_y);
		}
		else if (_action == GLFW_RELEASE) {
			is_rotate_camera = false;
		}
	}
}

void scroll_callback(Application::Handle _handle, double _xoffset, double _yoffset) {
	app.default_scroll_callback(_handle, _xoffset, _yoffset);
	camera_radius -= (float)(0.1 * _yoffset);
	camera_radius = clamp(camera_radius, 0.5f, 8.0f);
	update_camera();
}

int main(int argc, char* argv[]) {
	app.init("test", 800, 600);
	app.set_key_callback(key_callback);
	app.set_windowsize_callback(windowsize_callback);
	app.set_cursorpos_callback(cursorpos_callback);
	app.set_mousebutton_callback(mousebutton_callback);
	app.set_scroll_callback(scroll_callback);
	graphics.clear_color = vec4(0.1f, 0.2f, 0.3f, 1.0f);
	graphics.clear();

	new(&graphics.render_3d) ThreeD_Renderer(*new(&camera) Camera(vec3(0.0f, 1.0f, 5.0f), vec3(0.0f, 1.0f, 0.0f)));
	new(&graphics.oit) OIT_Renderer(*graphics.render_3d.camera);
	camera_yaw = 0.0f;
	camera_pitch = 0.0f;
	camera_radius = 5.0f;
	is_rotate_camera = false;
	new(&dir_light) DirLight(vec3(-0.2f, -1.0f, -0.3f), 0.05f, 0.4f, 0.5f);
	new(&point_light) PointLight(vec3(0.0f, 1.0f, 5.0f), 0.5f, 0.8f, 1.0f, vec3(1.0f), 0.0075f, 0.045f);

	TextLabel fps_label(
		vec3(96.0f, 48.0f, 0.0f), Appearance::color,
		vec4(0.0f, 0.0f, 0.0f, 0.0f), Rect(-96.0f, 0.0f, 192.0f, -48.0f),
		L"\\s16\\l16fps ", Direction::horizontal, Align::left, Align::top
	);

	new(&test_button) CommandButton(
		vec3(400.0f, 300.0f, 0.0f), Appearance::gradient_v,
		vec4(0.1f, 0.1f, 0.1f, 1.0f), Rect(-300.0f, 200.0f, 600.0f, -400.0f),
		L"\\s32\\l32测试 ", Direction::horizontal, Align::center, Align::center
	);

	animation.keyframes[0] = Sprite::Frame(vec3(0, 0, 0), vec3(0, 0, 0), vec2(1, 1),
		Color::get_default(8), Color::get_default(0));
	animation.keyframes[60] = Sprite::Frame(vec3(0, 1, 0), vec3(0, 0, 0), vec2(1, 1),
		Color::get_default(1), Color::get_default(0));
	animation.keyframes[180] = Sprite::Frame(vec3(0, -1, 0), vec3(0, 0, 0), vec2(1, 1),
		Color::get_default(2), Color::get_default(0));
	animation.keyframes[240] = Sprite::Frame(vec3(0, 0, 0), vec3(0, 0, 0), vec2(1, 1),
		Color::get_default(8), Color::get_default(0));

	Sprite::Animation button_animation(60, true);
	button_animation.keyframes[0] = Sprite::Frame(vec3(0, 0, 0), vec3(0, 0, 0), vec2(1, 1),
		Color::get_default(8), Color::get_default(0));
	button_animation.keyframes[60] = Sprite::Frame(vec3(-100, 100, 0), vec3(0, 0, 0), vec2(1, 1),
		Color::get_default(8), Color::get_default(0));
	button_animation.keyframes[180] = Sprite::Frame(vec3(100, -100, 0), vec3(0, 0, 0), vec2(1, 1),
		Color::get_default(8), Color::get_default(0));
	button_animation.keyframes[240] = Sprite::Frame(vec3(0, 0, 0), vec3(0, 0, 0), vec2(1, 1),
		Color::get_default(8), Color::get_default(0));

	test_button.play(button_animation, -1);

	for (int i = 0; i < 10; i++) {
		sprites[i] = new Sprite(
			vec3(-0.1f * i, 0.1f, -0.1f * i), "face_transparent.png", Square(0.0f, 0.0f, 1.0f)
		);
		//sprites[i]->mix_color.a = 1.0f;
		sprites[i]->mix_color.a = 1.0f - 0.1f * i;
	}

	string filenames[] = { "common.vert", "depth.frag" };
	uint types[] = { Shader::vertex, Shader::fragment };
	Program program(2, filenames, types);

	int cnt = 0;

	while (!app.exit_flag) {

		if (app.prev_time == app.cur_time) {
			fps_label.set_text(L"\\s16\\l16fps " + to_wstring(app.fps));
			if (cnt < 10)sprites[cnt++]->play(animation, cnt);
			test_button.set_text(L"\\s32\\l32\\ " + to_wstring(temp_new) + L"\\n" + to_wstring(temp_delete));
		}

		point_light.position = graphics.render_3d.camera->position;

		app.update();
		//graphics.draw(Square(-1.0f, -1.0f, 2.0f), program);
		for (int i = 0; i < 10; i++) {
			(*sprites[i]).update();
		}
		if (test_button.responder.down_flag) {
			test_button.translation.x = (float)app.cursor_x;
			test_button.translation.y = (float)app.cursor_y;
		}
		test_button.update();
		fps_label.update(); 

		graphics.set_renderer(graphics.render_3d);

		graphics.set_renderer(graphics.oit);
		for (int i = 0; i < 10; i++) {
			sprites[i]->render();
		}

		graphics.set_renderer(graphics.render_2d);
		fps_label.render();
		test_button.render();

	}

	app.done();

	return 0;
}