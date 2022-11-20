#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*-----------------------------------------------------------------------------------------------*/

void InitSystem() {

	if (!glfwInit()) {
#ifdef _DEBUG
		std::cerr << "Error: failed to initialize glfw" << std::endl;
#endif // _DEBUG
	}

}

void DestroySystem() {

	glfwTerminate();

}