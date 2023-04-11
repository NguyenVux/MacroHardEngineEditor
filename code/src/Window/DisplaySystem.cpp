#include "DisplaySystem.h"

CreateWindowResult DisplaySystem::CreateWindow(std::string i_title, int i_width, int i_height)
{
	LOG_INFO("Create GLFW Window", "DisplaySystem");
	GLFWwindow* win = glfwCreateWindow(i_width, i_height, i_title.c_str(), nullptr, nullptr);
	if (win == nullptr)
	{
		LOG_ERROR("Cannot create GLFW Window", "DisplaySystem");
		return CreateWindowError(CannotCreateWindow);
	}
	glfwMakeContextCurrent(win);
	int version = gladLoaderLoadGL();
	if (version == 0)
	{
		LOG_ERROR("Cannot load OpenGL function", "DisplaySystem");
		return CreateWindowError(CannotLoadGL);
	}

	return std::make_shared<Window>(win);
}
