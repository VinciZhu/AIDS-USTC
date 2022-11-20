#pragma once
#include "core.hpp"
namespace znd {

	bool Node::LessZ::operator()(const Node* a, const Node* b) {
		float z1 = a->translation.z, z2 = b->translation.z;
		while (a = a->super)z1 += a->translation.z;
		while (b = b->super)z2 += b->translation.z;
		return z1 < z2;
	}

	bool Node::GreaterZ::operator()(const Node* a, const Node* b) {
		float z1 = a->translation.z, z2 = b->translation.z;
		while (a = a->super)z1 += a->translation.z;
		while (b = b->super)z2 += b->translation.z;
		return z1 > z2;
	}

	Node::Node() {
	}

	Node::Node(const vec3& _translation, const vec3& _rotation, const vec3& _scaling) {
		super = nullptr;
		subs.clear();
		translation = _translation;
		rotation = _rotation;
		scaling = _scaling;
		update_trans_mat();
		actions.clear();
		destroyed_actions.clear();
		prev_time = app.cur_time;
	}

	Node::~Node() {
	}

	void Node::update_trans_mat() {
		trans_mat = translate(mat4(1.0f), translation)
			* rotate(mat4(1.0f), rotation.x, vec3(1.0f, 0.0f, 0.0f))
			* rotate(mat4(1.0f), rotation.z, vec3(0.0f, 0.0f, 1.0f))
			* rotate(mat4(1.0f), rotation.y, vec3(0.0f, 1.0f, 0.0f))
			* scale(mat4(1.0f), scaling);
		if (super) {
			trans_mat = super->trans_mat * trans_mat;
		}
	}

	void Node::set_super(Node* _super) {
		if (super) {
			super->subs.erase(find(super->subs.begin(), super->subs.end(), this));
		}
		super = _super;
		_super->subs.push_back(this);
	}

	Action* Node::wait(double _duration, Action* _prev) {
		Action* ptr = _prev;
		if (_duration) {
			play(ptr = new Action(nullptr, 0.0f, _duration, _prev));
		}
		return ptr;
	}

	Action* Node::translate_to(const vec3& _translation, double _duration) {
		Action* ptr = nullptr;
		if (_translation.x != translation.x) {
			play(ptr = new Action(&translation.x, _translation.x - translation.x, _duration));
		}
		if (_translation.y != translation.y) {
			play(ptr = new Action(&translation.y, _translation.y - translation.y, _duration));
		}
		if (_translation.z != translation.z) {
			play(ptr = new Action(&translation.z, _translation.z - translation.z, _duration));
		}
		return ptr;
	}

	Action* Node::translate_by(const vec3& _translation, double _duration, Action* _prev) {
		Action* ptr = _prev;
		if (_translation.x) {
			play(ptr = new Action(&translation.x, _translation.x, _duration, _prev));
		}
		if (_translation.y) {
			play(ptr = new Action(&translation.y, _translation.y, _duration, _prev));
		}
		if (_translation.z) {
			play(ptr = new Action(&translation.z, _translation.z, _duration, _prev));
		}
		return ptr;
	}

	Action* Node::rotate_to(const vec3& _rotation, double _duration) {
		Action* ptr = nullptr;
		if (_rotation.x != rotation.x) {
			play(ptr = new Action(&rotation.x, _rotation.x - rotation.x, _duration));
		}
		if (_rotation.y != rotation.y) {
			play(ptr = new Action(&rotation.y, _rotation.y - rotation.y, _duration));
		}
		if (_rotation.z != rotation.z) {
			play(ptr = new Action(&rotation.z, _rotation.z - rotation.z, _duration));
		}
		return ptr;
	}

	Action* Node::rotate_by(const vec3& _rotation, double _duration, Action* _prev) {
		Action* ptr = _prev;
		if (_rotation.x) {
			play(ptr = new Action(&rotation.x, _rotation.x, _duration, _prev));
		}
		if (_rotation.y) {
			play(ptr = new Action(&rotation.y, _rotation.y, _duration, _prev));
		}
		if (_rotation.z) {
			play(ptr = new Action(&rotation.z, _rotation.z, _duration, _prev));
		}
		return ptr;
	}

	Action* Node::scale_to(const vec3& _scaling, double _duration) {
		Action* ptr = nullptr;
		if (_scaling.x != scaling.x) {
			play(ptr = new Action(&scaling.x, _scaling.x - scaling.x, _duration));
		}
		if (_scaling.y != scaling.y) {
			play(ptr = new Action(&scaling.y, _scaling.y - scaling.y, _duration));
		}
		if (_scaling.z != scaling.z) {
			play(ptr = new Action(&scaling.z, _scaling.z - scaling.z, _duration));
		}
		return ptr;
	}

	Action* Node::scale_by(const vec3& _scaling, double _duration, Action* _prev) {
		Action* ptr = _prev;
		if (_scaling.x != 1.0f) {
			play(ptr = new Action(&scaling.x, _scaling.x - scaling.x, _duration, _prev));
		}
		if (_scaling.y != 1.0f) {
			play(ptr = new Action(&scaling.y, _scaling.y - scaling.y, _duration, _prev));
		}
		if (_scaling.z != 1.0f) {
			play(ptr = new Action(&scaling.z, _scaling.z - scaling.z, _duration, _prev));
		}
		return ptr;
	}

	void Node::play(Action* _action) {
		_action->pause_flag = false;
		actions.push_back(_action);
	}

	void Node::stop(Action* _action) {
		_action->pause_flag = true;
		if (_action->target != this) {
			_action->target = this;
			destroyed_actions.push_back(_action);
			for (uint i = 0; i < _action->next.size(); ++i) {
				stop(_action->next[i]);
			}
		}
	}

	bool Node::update_action(Action* _action) {
		if (!_action->pause_flag) {
			bool stop_flag;
			double prev = _action->delta_time / _action->duration;
			double cur = (_action->delta_time += app.cur_time - prev_time) / _action->duration;
			if (stop_flag = cur >= 1.0) {
				cur = 1.0;
			}
			if (_action->target) {
				*(float*)_action->target += (float)((cur - prev) * _action->value.f);
			}
			return stop_flag;
		}
		else {
			return false;
		}
	}

	void Node::update_actions() {
		uint n = actions.size();
		for (uint i = 0; i < n; ++i) {
			Action* action = actions[i];
			if (action->target == this) {
				actions.erase(actions.begin() + i--);
				--n;
			}
			else if (update_action(action)) {
				bool destroy_flag = !--action->repeat;
				action->delta_time = 0.0;
				for (uint i = 0; i < action->next.size(); ++i) {
					if (action->next[i]->repeat) {
						destroy_flag = false;
						actions.push_back(action->next[i]);
					}
				}
				if (destroy_flag) {
					for (uint i = 0; i < action->next.size(); ++i) {
						action->next[i]->prev = nullptr;
					}
					do {
						action = actions[i]->prev;
						if (action) {
							action->next.erase(find(action->next.begin(), action->next.end(), actions[i]));
						}
						delete actions[i];
						actions[i] = action;
					} while (action && !action->repeat && !action->next.size());
				}
				actions.erase(actions.begin() + i--);
				--n;
			}
		}
		for (uint i = 0; i < destroyed_actions.size(); ++i) {
			delete destroyed_actions[i];
		}
		destroyed_actions.clear();
		prev_time = app.cur_time;
	}

	void Node::update() {
		update_actions();
		update_trans_mat();
	}

}
