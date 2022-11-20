#pragma once
#include "core.hpp"
namespace znd {

	Sprite::Sprite() {
	}

	Sprite::Sprite(const Node& _node, const Texture* _texture, const Rect& _rect) :
		Node(_node.translation, _node.rotation, _node.scaling) {
		color = vec4(1.0f, 1.0f, 1.0f, 0.0f);
		mix_color = vec4(1.0f);
		texture = const_cast<Texture*>(_texture);
		rsp_ptr = nullptr;
		ebo = create_ebo();
		vbo = create_vbo();
		vao = create_vao(vbo, ebo);
		set_rect(_rect);
	}

	Sprite::Sprite(const vec3& _translation, const Texture* _texture, const Rect& _rect) :
		Node(_translation) {
		color = vec4(1.0f, 1.0f, 1.0f, 0.0f);
		mix_color = vec4(1.0f);
		texture = const_cast<Texture*>(_texture);
		rsp_ptr = nullptr;
		ebo = create_ebo();
		vbo = create_vbo();
		vao = create_vao(vbo, ebo);
		set_rect(_rect);
	}

	Sprite::Sprite(const Node& _node, const string& _filename, const Rect& _rect) {
		new(this) Sprite(_node, &Texture::get(_filename, Texture::common), _rect);
	}

	Sprite::Sprite(const vec3& _translation, const string& _filename, const Rect& _rect) {
		new(this) Sprite(_translation, &Texture::get(_filename, Texture::common), _rect);
	}

	Sprite::~Sprite() {
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	uint Sprite::create_vao(uint _vbo, uint _ebo) {
		uint vao;
		glCreateVertexArrays(1, &vao);
		glEnableVertexArrayAttrib(vao, 0);
		glEnableVertexArrayAttrib(vao, 2);
		glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayVertexBuffer(vao, 0, _vbo, 0, 12);
		glVertexArrayVertexBuffer(vao, 1, _vbo, 48, 8);
		glVertexArrayAttribBinding(vao, 0, 0);
		glVertexArrayAttribBinding(vao, 2, 1);
		glVertexArrayElementBuffer(vao, _ebo);
		return vao;
	}

	uint Sprite::create_vbo() {
		uint vbo;
		glCreateBuffers(1, &vbo);
		glNamedBufferStorage(vbo, 80, NULL, GL_DYNAMIC_STORAGE_BIT);
		glNamedBufferSubData(vbo, 48, 32, graphics.tex_coords);
		return vbo;
	}

	uint Sprite::create_ebo() {
		return graphics.create_quad_ebo();
	}

	void Sprite::set_rect(const Rect& _rect) {
		rect = _rect;
		glNamedBufferSubData(vbo, 0, 48, rect.coords);
	}

	void Sprite::render() {
		graphics.renderer->render_sprite(*this);
	}

	Action* Sprite::change_color_to(const vec4& _color, double _duration) {
		Action* ptr = nullptr;
		if (_color.r != color.r) {
			play(ptr = new Action(&color.r, _color.r - color.r, _duration));
		}
		if (_color.g != color.g) {
			play(ptr = new Action(&color.g, _color.g - color.g, _duration));
		}
		if (_color.b != color.b) {
			play(ptr = new Action(&color.b, _color.b - color.b, _duration));
		}
		if (_color.a != color.a) {
			play(ptr = new Action(&color.a, _color.a - color.a, _duration));
		}
		return ptr;
	}

	Action* Sprite::change_mix_color_to(const vec4& _mix_color, double _duration) {
		Action* ptr = nullptr;
		if (_mix_color.r != mix_color.r) {
			play(ptr = new Action(&mix_color.r, _mix_color.r - mix_color.r, _duration));
		}
		if (_mix_color.g != mix_color.g) {
			play(ptr = new Action(&mix_color.g, _mix_color.g - mix_color.g, _duration));
		}
		if (_mix_color.b != mix_color.b) {
			play(ptr = new Action(&mix_color.b, _mix_color.b - mix_color.b, _duration));
		}
		if (_mix_color.a != mix_color.a) {
			play(ptr = new Action(&mix_color.a, _mix_color.a - mix_color.a, _duration));
		}
		return ptr;
	}

	void Sprite::play(Animate* _animate) {
		_animate->pause_flag = false;
		animates.push_back(_animate);
		for (auto itr = _animate->root_actions.begin(); itr != _animate->root_actions.end(); ++itr) {
			play(*itr);
		}
	}

	void Sprite::pause(Animate* _animate) {
		_animate->set_pause_flag(true);
	}

	void Sprite::resume(Animate* _animate) {
		_animate->set_pause_flag(false);
	}

	void Sprite::stop(Animate* _animate) {
		_animate->pause_flag = true;
		for (auto itr = _animate->root_actions.begin(); itr != _animate->root_actions.end(); ++itr) {
			stop(*itr);
		}
		_animate->root_actions.clear(); 
		animates.erase(find(animates.begin(), animates.end(), _animate));
	}

	void Sprite::play(const Animation& _animation, int _loop) {
		Animate& animate = Animate::get(*this, &_animation);
		if (animate.root_actions.size()) {
			stop(&animate);
		}
		animate.generate_actions(*this, _animation, _loop);
		play(&animate);
	}

	void Sprite::pause(const Animation& _animation) {
		pause(&Animate::get(*this, &_animation));
	}

	void Sprite::resume(const Animation& _animation) {
		resume(&Animate::get(*this, &_animation));
	}

	void Sprite::stop(const Animation& _animation) {
		stop(&Animate::get(*this, &_animation));
	}

	bool Sprite::update_action(Action* _action) {
		if (!_action->pause_flag) {
			bool stop_flag;
			double prev = _action->delta_time / _action->duration;
			double cur = (_action->delta_time += app.cur_time - prev_time) / _action->duration;
			stop_flag = cur >= 1.0;
			if (_action->target) {
				if (stop_flag) {
					cur = 1.0;
					if (_action->target == &texture) {
						*(Texture**)_action->target = (Texture*)_action->value.p;
						return true;
					}
					else if (_action->target == &rect) {
						*(Rect*)_action->target = *(Rect*)_action->value.p;
						return true;
					}
				}
				*(float*)_action->target += (float)((cur - prev) * _action->value.f);
			}
			return stop_flag;
		}
		else {
			return false;
		}
	}

	void Sprite::update_animates() {
		uint n = animates.size();
		for (uint i = 0; i < n; ++i) {
			if (!animates[i]->root_actions[0]->prev->repeat) {
				stop(animates[i]);
			}
		}
	}

	void Sprite::update() {
		update_animates();
		Node::update();
	}

	Sprite::Frame::Frame(
		const vec3& _translation, const vec3& _rotation, const vec2& _scaling,
		const vec4& _color, const vec4& _mix_color, const Texture* _texture, const Rect& _rect
	) {
		translation = _translation;
		rotation = _rotation;
		scaling = vec3(_scaling, 1.0f);
		color = _color;
		mix_color = _mix_color;
		texture = const_cast<Texture*>(_texture);
		rect = _rect;
	}

	Sprite::Frame::Frame(const Sprite& _sprite) {
		translation = _sprite.translation;
		rotation = _sprite.rotation;
		scaling = _sprite.scaling;
		color = _sprite.color;
		mix_color = _sprite.mix_color;
		rect = _sprite.rect;
		texture = _sprite.texture;
	}

	Sprite::Animation::Animation() {
	}

	Sprite::Animation::Animation(uint _fps, bool _relative_flag, bool _texture_flag, bool _rect_flag) {
		fps = _fps;
		relative_flag = _relative_flag;
		texture_flag = _texture_flag;
		rect_flag = _rect_flag;
	}

	Sprite::Animation::Animation(
		uint _fps, uint _size, const uint _times[], const Frame _frames[],
		bool _relative_flag, bool _texture_flag, bool _rect_flag
	) {
		new(this) Animation(_fps,_relative_flag, _texture_flag, _rect_flag);
		for (uint i = 0; i < _size; ++i) {
			keyframes[_times[i]] = _frames[i];
		}
	}

	Sprite::Animation::~Animation() {
	}

	void Sprite::Animate::set_pause_flag(bool _flag) {
		pause_flag = _flag;
		for (auto itr = root_actions.begin(); itr != root_actions.end(); ++itr) {
			(*itr)->set_pause_flag(_flag);
		}
	}

	void Sprite::Animate::generate_actions(Sprite& _sprite, const Animation& _animation, int _loop) {
		multimap<uint, Action*, greater<uint>> prev_actions;
		Frame origin_frame;
		if (_animation.relative_flag) {
			origin_frame.color = _sprite.color;
			origin_frame.texture = _sprite.texture;
			origin_frame.rect = _sprite.rect;
		}
		else {
			new(&origin_frame) Frame(_sprite);
		}
		uint prev_time = 0, cur_time;
		uint period = (*--_animation.keyframes.end()).first;
		const Frame *prev_frame = &origin_frame, *cur_frame;
		for (auto itr = _animation.keyframes.begin(); itr != _animation.keyframes.end(); ++itr) {
			cur_time = (*itr).first;
			cur_frame = &(*itr).second;
			double duration = glm::max(1.0 * (cur_time - prev_time) / _animation.fps, 1e-5);
			Action* action;
			if (cur_frame->translation.x != prev_frame->translation.x) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.translation.x, cur_frame->translation.x - prev_frame->translation.x, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.translation.x, cur_frame->translation.x - prev_frame->translation.x, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.translation.x, cur_frame->translation.x - prev_frame->translation.x, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->translation.y != prev_frame->translation.y) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.translation.y, cur_frame->translation.y - prev_frame->translation.y, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.translation.y, cur_frame->translation.y - prev_frame->translation.y, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.translation.y, cur_frame->translation.y - prev_frame->translation.y, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->translation.z != prev_frame->translation.z) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.translation.z, cur_frame->translation.z - prev_frame->translation.z, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.translation.z, cur_frame->translation.z - prev_frame->translation.z, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.translation.z, cur_frame->translation.z - prev_frame->translation.z, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->rotation.x != prev_frame->rotation.x) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.rotation.x, cur_frame->rotation.x - prev_frame->rotation.x, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.rotation.x, cur_frame->rotation.x - prev_frame->rotation.x, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.rotation.x, cur_frame->rotation.x - prev_frame->rotation.x, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->rotation.y != prev_frame->rotation.y) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.rotation.y, cur_frame->rotation.y - prev_frame->rotation.y, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.rotation.y, cur_frame->rotation.y - prev_frame->rotation.y, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.rotation.y, cur_frame->rotation.y - prev_frame->rotation.y, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->rotation.z != prev_frame->rotation.z) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.rotation.z, cur_frame->rotation.z - prev_frame->rotation.z, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.rotation.z, cur_frame->rotation.z - prev_frame->rotation.z, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.rotation.z, cur_frame->rotation.z - prev_frame->rotation.z, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->scaling.x != prev_frame->scaling.x) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.scaling.x, _sprite.scaling.x * cur_frame->scaling.x - _sprite.scaling.x * prev_frame->scaling.x, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.scaling.x, _sprite.scaling.x * cur_frame->scaling.x - _sprite.scaling.x * prev_frame->scaling.x, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.scaling.x, _sprite.scaling.x * cur_frame->scaling.x - _sprite.scaling.x * prev_frame->scaling.x, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->scaling.y != prev_frame->scaling.y) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.scaling.y, _sprite.scaling.y * cur_frame->scaling.y - _sprite.scaling.y * prev_frame->scaling.y, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.scaling.y, _sprite.scaling.y * cur_frame->scaling.y - _sprite.scaling.y * prev_frame->scaling.y, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.scaling.y, _sprite.scaling.y * cur_frame->scaling.y - _sprite.scaling.y * prev_frame->scaling.y, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->color.r != prev_frame->color.r) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.color.r, cur_frame->color.r - prev_frame->color.r, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.color.r, cur_frame->color.r - prev_frame->color.r, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.color.r, cur_frame->color.r - prev_frame->color.r, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->color.g != prev_frame->color.g) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.color.g, cur_frame->color.g - prev_frame->color.g, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.color.g, cur_frame->color.g - prev_frame->color.g, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.color.g, cur_frame->color.g - prev_frame->color.g, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->color.b != prev_frame->color.b) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.color.b, cur_frame->color.b - prev_frame->color.b, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.color.b, cur_frame->color.b - prev_frame->color.b, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.color.b, cur_frame->color.b - prev_frame->color.b, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->color.a != prev_frame->color.a) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.color.a, cur_frame->color.a - prev_frame->color.a, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.color.a, cur_frame->color.a - prev_frame->color.a, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.color.a, cur_frame->color.a - prev_frame->color.a, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->mix_color.r != prev_frame->mix_color.r) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.mix_color.r, _sprite.mix_color.r * cur_frame->mix_color.r - _sprite.mix_color.r * prev_frame->mix_color.r, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.mix_color.r, _sprite.mix_color.r * cur_frame->mix_color.r - _sprite.mix_color.r * prev_frame->mix_color.r, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.mix_color.r, _sprite.mix_color.r * cur_frame->mix_color.r - _sprite.mix_color.r * prev_frame->mix_color.r, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->mix_color.g != prev_frame->mix_color.g) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.mix_color.g, _sprite.mix_color.g * cur_frame->mix_color.g - _sprite.mix_color.g * prev_frame->mix_color.g, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.mix_color.g, _sprite.mix_color.g * cur_frame->mix_color.g - _sprite.mix_color.g * prev_frame->mix_color.g, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.mix_color.g, _sprite.mix_color.g * cur_frame->mix_color.g - _sprite.mix_color.g * prev_frame->mix_color.g, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->mix_color.b != prev_frame->mix_color.b) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.mix_color.b, _sprite.mix_color.b * cur_frame->mix_color.b - _sprite.mix_color.b * prev_frame->mix_color.b, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.mix_color.b, _sprite.mix_color.b * cur_frame->mix_color.b - _sprite.mix_color.b * prev_frame->mix_color.b, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.mix_color.b,_sprite.mix_color.b * cur_frame->mix_color.b - _sprite.mix_color.b * prev_frame->mix_color.b, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (cur_frame->mix_color.a != prev_frame->mix_color.a) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.mix_color.a, _sprite.mix_color.a * cur_frame->mix_color.a - _sprite.mix_color.a * prev_frame->mix_color.a, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.mix_color.a, _sprite.mix_color.a * cur_frame->mix_color.a - _sprite.mix_color.a * prev_frame->mix_color.a, duration, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.mix_color.a, _sprite.mix_color.a * cur_frame->mix_color.a - _sprite.mix_color.a * prev_frame->mix_color.a, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (_animation.texture_flag && cur_frame->texture != prev_frame->texture) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.texture, cur_frame->texture, duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.texture, cur_frame->texture, _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.texture, cur_frame->texture, duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			if (_animation.rect_flag && rects[cur_time] != rects[prev_time]) {
				auto prev = prev_actions.upper_bound(cur_time);
				if (prev == prev_actions.end()) {
					action = new Action(
						&_sprite.rect, rects[cur_time], duration, -1
					);
					root_actions.push_back(action);
					prev_actions.insert(make_pair(cur_time, action));
				}
				else {
					uint delta_time = prev_time - (*prev).first;
					if (delta_time) {
						action = new Action(
							nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
						);
						action = new Action(
							&_sprite.rect, rects[cur_time], _loop, action
						);
					}
					else {
						action = new Action(
							&_sprite.rect, rects[cur_time], duration, _loop, (*prev).second
						);
					}
					if (prev != --prev_actions.end()) {
						prev_actions.erase(prev);
					}
					prev_actions.insert(make_pair(cur_time, action));
				}
			}
			prev_time = cur_time;
			prev_frame = cur_frame;
		}
		for (uint i = 0; i < root_actions.size(); ++i) {
			auto prev = prev_actions.lower_bound(period);
			uint delta_time = period - (*prev).first;
			if (delta_time) {
				root_actions[i]->set_prev(new Action(
					nullptr, 0.0f, 1.0 * delta_time / _animation.fps, _loop, (*prev).second
				));
			}
			else {
				root_actions[i]->set_prev((*prev).second);
			}
			if (prev != --prev_actions.end()) {
				prev_actions.erase(prev);
			}
		}
	}

	Sprite::Animate::Animate() {
	}

	Sprite::Animate::Animate(const Animation& _animation) {
		pause_flag = false;
		for (auto itr = _animation.keyframes.begin(); itr != _animation.keyframes.end(); ++itr) {
			rects[itr->first] = new Rect(itr->second.rect);
		}
	}

	Sprite::Animate::~Animate() {
		for (auto itr = rects.begin(); itr != rects.end(); ++itr) {
			delete itr->second;
		}
	}

	Sprite::Animate& Sprite::Animate::get(const Sprite& _sprite, const Animation* _animation) {
		auto& animate_cache = const_cast<Sprite*>(&_sprite)->animate_cache;
		auto itr = animate_cache.find(const_cast<Animation*>(_animation));
		if (itr == animate_cache.end()) {
			return *(animate_cache[const_cast<Animation*>(_animation)] = new Animate(*_animation));
		}
		else {
			return *itr->second;
		}
	}

}