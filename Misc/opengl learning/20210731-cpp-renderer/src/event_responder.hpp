#pragma once
#include "core.hpp"
namespace znd {

	EventResponder::EventResponder() {
	}

	EventResponder::EventResponder(
		void(*_down_callback)(), void(*_up_callback)(),
		void(*_in_callback)(), void(*_out_callback)()
	) {
		down_flag = false;
		in_flag = false;
		down_callback = _down_callback;
		up_callback = _up_callback;
		in_callback = _in_callback;
		out_callback = _out_callback;
	};

	EventResponder::~EventResponder() {
	}

	void EventResponder::down() {
		cout << "down";
		app.cur_responder->down_flag = true;
		if (down_callback) {
			down_callback();
		}
	}

	void EventResponder::up() {
		cout << "up";
		app.cur_responder->down_flag = false;
		if (up_callback) {
			up_callback();
		}
	}

	void EventResponder::in() {
		cout << "in";
		app.cur_responder->in_flag = true;
		if (in_callback) {
			in_callback();
		}
	}

	void EventResponder::out() {
		cout << "out";
		app.prev_responder->in_flag = false;
		if (out_callback) {
			out_callback();
		}
	}

}
