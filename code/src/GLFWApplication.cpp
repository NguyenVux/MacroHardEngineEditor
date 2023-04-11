#include <memory>
#include "GLFWApplication.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include "glad/wgl.h"

GLFWApplication::GLFWApplication()
{
	glfwInit();
}
ApplicationInitResult GLFWApplication::init()
{
	{
		int glfwInitResult = glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		if (glfwInitResult != GLFW_TRUE)
		{
			return ApplicationInitResult(ApplicationInitError(ApplicationInitErrorCode::CannotInitGLFW));
		}
	}
	{
		int glLoadResult = gladLoadGL(glfwGetProcAddress);
		if (glLoadResult == GL_FALSE)
		{
			return ApplicationInitResult(ApplicationInitError(ApplicationInitErrorCode::CannotLoadGLFunc));
		}

	}
	return ApplicationInitResult();
}

GLFWApplication::~GLFWApplication() {
	glfwTerminate();
	std::cout << "Application Destroyed" << std::endl;
}