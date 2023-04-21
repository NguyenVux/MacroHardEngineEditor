#include <chrono>
#include <iostream>
#include "GLFWApplication.h"
#include "Window/DisplaySystem.h"
#include "Graphic/Shader.h"
#include "Graphic/ShaderProgram.h"

void glfwErrorCallBack(int error_code, const char* description)
{
	LOG_ERROR("[" + std::to_string(error_code) + "]" + description, "GLFW");
}
int main() {
	Logger::LoggerSystem::InitLogger(std::make_unique<Logger::StdIOLogger>());

	LOG_INFO("Initializing glfw", "MAIN");
	int glfwInitResult = glfwInit();
	if (glfwInitResult != GLFW_TRUE)
	{
		return -1;
	}

	std::shared_ptr<Window> win;
	{
		DisplaySystem displaySystem;
		auto createWindowResult = displaySystem.CreateWindow("Hello World", 1280, 720);
		if (createWindowResult != MHTL::success)
		{
			LOG_ERROR("Failed to create window", "MAIN");
			return -2;
		}
		win = createWindowResult.extract_payload();
	}


	std::unique_ptr<GLFWApplication> application = std::make_unique<GLFWApplication>(win);
	std::chrono::steady_clock::time_point previousTime = std::chrono::steady_clock::now();
	application->Start();
	while (!win->ShouldClose())
	{
		glfwPollEvents();
		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> frameTime = currentTime - previousTime;
		application->Update(frameTime.count());
		previousTime = currentTime;
	}
}