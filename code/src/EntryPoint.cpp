#include <chrono>
#include <memory>
#include <iostream>
#include "GLFWApplication.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "GLFW/glfw3.h"
#include "Window/Window.h"


void main() {
	auto result = glfwInit();
	std::unique_ptr<GLFWApplication> application = std::make_unique<GLFWApplication>();
	ApplicationInitResult appInitResult = application->init();

	if (appInitResult != MHTL::success)
	{
		return;
	}
	Window win(800,600,"Hello World");
	while (!win.ShouldClose())
	{
		glfwPollEvents();
	}
}