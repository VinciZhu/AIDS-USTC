#pragma once

#include "SystemBase.hpp"

/*-----------------------------------------------------------------------------------------------*/
struct _SystemWindow {
	GLFWwindow* handle;
	GLboolean should_close;

	const GLchar* caption;
	GLsizei width, height, depth;
	GLsizei pixels_num;
	GLfloat aspect_ratio;
	glm::mat4 ortho_mat;

	glm::vec4 clear_color;
} * SystemWindow;

void InitSystemWindow(const GLchar* caption, GLsizei width, GLsizei height, GLsizei depth);

void UpdateSystemWindow();

void DestroySystemWindow();

void RefreshSystemWindow();

void SetSystemKeyCallback(GLFWkeyfun callback);

void ProcessSystemEvents();

void SetSystemWindowClearColor(glm::vec4 color);

void ClearSystemGraphics();

void SystemWindowSizeCallback(GLFWwindow* window, int width, int height);
/*-----------------------------------------------------------------------------------------------*/

void InitSystemWindow(const GLchar* caption, GLsizei width, GLsizei height, GLsizei depth) {
	GLFWwindow* window;
	window = glfwCreateWindow(width, height, caption, NULL, NULL);
	if (!window) {
#ifdef _DEBUG
		std::cerr << "Error: failed to create glfw window" << std::endl;
#endif // _DEBUG
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, SystemWindowSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
#ifdef _DEBUG
		std::cerr << "Error: failed load gl with glad" << std::endl;
#endif // _DEBUG
	}

	SystemWindow = new struct _SystemWindow;
	SystemWindow->handle = window;
	SystemWindow->should_close = GL_FALSE;
	SystemWindow->caption = caption;
	SystemWindow->width = width;
	SystemWindow->height = height;
	SystemWindow->depth = depth;
	SystemWindow->pixels_num = width * height;
	SystemWindow->aspect_ratio = 1.0f * width / height;
	SystemWindow->ortho_mat = glm::ortho(
		0.0f, 1.0f * width,
		1.0f * height, 0.0f,
		-1.0f * depth, 0.0f
	); 
	SetSystemWindowClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	ClearSystemGraphics();
}

void UpdateSystemWindow() {
	SystemWindow->should_close = glfwWindowShouldClose(SystemWindow->handle);
}

void DestroySystemWindow() {
	glfwDestroyWindow(SystemWindow->handle);
	delete SystemWindow;
}

void RefreshSystemWindow() {
	glfwSwapBuffers(SystemWindow->handle);
	ClearSystemGraphics();
}

void SetSystemWindowClearColor(glm::vec4 color) {
	glClearColor(SystemWindow->clear_color.r, SystemWindow->clear_color.g,
		SystemWindow->clear_color.b, SystemWindow->clear_color.a);
	SystemWindow->clear_color = color;
}

void ClearSystemGraphics() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SetSystemKeyCallback(GLFWkeyfun callback) {
	glfwSetKeyCallback(SystemWindow->handle, callback);
}

void ProcessSystemEvents() {
	glfwPollEvents();
}

void SystemWindowSizeCallback(GLFWwindow* window, int width, int height) {
	GLsizei w = glm::min((int)(height * SystemWindow->aspect_ratio), width);
	GLsizei h = glm::min((int)(width / SystemWindow->aspect_ratio), height);
	glViewport((width - w) / 2, (height - h) / 2, w, h);
}