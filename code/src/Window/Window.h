#pragma once
#include <string>
#include "IWindow.h"
#include "GLFW/glfw3.h"

class Window : public IWinwdow {
private:
	GLFWwindow* m_glfwWindow;
public:
	Window(int i_width, int i_height, std::string i_title);
	void UseContext();
	bool ShouldClose();
	void Present();
	~Window();
};