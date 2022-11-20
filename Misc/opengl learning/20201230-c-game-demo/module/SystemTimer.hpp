#pragma once

#include "SystemBase.hpp"

/*-----------------------------------------------------------------------------------------------*/
struct _SystemTimer {
	GLdouble cur;
	GLuint fps;
	GLboolean fps_updated;
	GLuint frame_cnt;
	GLdouble last_second;
} * SystemTimer;

void InitSystemTimer();

void UpdateSystemTimer();

void DestroySystemTimer();

/*-----------------------------------------------------------------------------------------------*/

void InitSystemTimer() {
	SystemTimer = new struct _SystemTimer;
	SystemTimer->cur = glfwGetTime();
	SystemTimer->fps = 1;
	SystemTimer->fps_updated = GL_TRUE;
	SystemTimer->frame_cnt = 1;
	SystemTimer->last_second = SystemTimer->cur;
	srand((GLuint)time(NULL));
}

void UpdateSystemTimer() {
	SystemTimer->cur = glfwGetTime();
	++SystemTimer->frame_cnt;
	if (SystemTimer->cur - SystemTimer->last_second >= 1) {
		SystemTimer->fps = SystemTimer->frame_cnt;
		SystemTimer->fps_updated = GL_TRUE;
		SystemTimer->frame_cnt = 1;
		SystemTimer->last_second = SystemTimer->cur;
	}
}

void DestroySystemTimer() {
	delete SystemTimer;
}