#pragma once
#include "core.hpp"
namespace znd {

	uint temp_new;//
	uint temp_delete;//

	Action::Action() {
	}

	Action::Action(uint _type, float _value, double _duration, Action* _prev) {
		new(this) Action(_type, _value, _duration, 1, _prev);
	}

	Action::Action(uint _type, float _value, double _duration, int _repeat, Action* _prev) {
		++temp_new;	//
		value.f = _value;
		duration = _duration;
		repeat = _repeat;
		next.clear();
		prev = _prev;
		if (_prev) {
			_prev->next.push_back(this);
		}
		delta_time = 0.0;
		pause_flag = false;
	}

	Action::Action(void* _target, float _value, double _duration, Action* _prev) {
		new(this) Action(_target, _value, _duration, 1, _prev);
	}

	Action::Action(void* _target, uint _value, double _duration, Action* _prev) {
		new(this) Action(_target, _value, _duration, 1, _prev);
	}

	Action::Action(void* _target, void* _value, double _duration, Action* _prev) {
		new(this) Action(_target, _value, _duration, 1, _prev);
	}

	Action::Action(void* _target, float _value, double _duration, int _repeat, Action* _prev) {
		++temp_new;	//
		target = _target;
		value.f = _value;
		duration = _duration;
		repeat = _repeat;
		next.clear();
		prev = _prev;
		if (_prev) {
			_prev->next.push_back(this);
		}
		delta_time = 0.0;
		pause_flag = false;
	}

	Action::Action(void* _target, uint _value, double _duration, int _repeat, Action* _prev) {
		++temp_new;	//
		target = _target;
		value.u = _value;
		duration = _duration;
		repeat = _repeat;
		next.clear();
		prev = _prev;
		if (_prev) {
			_prev->next.push_back(this);
		}
		delta_time = 0.0;
		pause_flag = false;
	}

	Action::Action(void* _target, void* _value, double _duration, int _repeat, Action* _prev) {
		++temp_new;	//
		target = _target;
		value.p = _value;
		duration = _duration;
		repeat = _repeat;
		next.clear();
		prev = _prev;
		if (_prev) {
			_prev->next.push_back(this);
		}
		delta_time = 0.0;
		pause_flag = false;
	}

	void Action::set_prev(Action* _prev) {
		prev = _prev;
		if (_prev) {
			_prev->next.push_back(this);
		}
	}

	void Action::set_pause_flag(bool _flag) {
		if (pause_flag != _flag) {
			pause_flag = _flag;
			for (uint i = 0; i < next.size(); ++i) {
				next[i]->set_pause_flag(_flag);
			}
		}
	}

	Action::~Action() {
		++temp_delete;	//
	}

}
