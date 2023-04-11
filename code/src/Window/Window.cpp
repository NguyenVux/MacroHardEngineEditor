#include "Window.h"
Window::Window(int i_width, int i_height, std::string i_title)
{
	m_glfwWindow = glfwCreateWindow(i_width, i_height, i_title.c_str(), nullptr, nullptr);
	glfwShowWindow(m_glfwWindow);
}

void Window::UseContext()
{
	if (m_glfwWindow != nullptr)
	{
		glfwMakeContextCurrent(m_glfwWindow);
	}
}

bool Window::ShouldClose()
{
	if (m_glfwWindow == nullptr)
	{
		return false;
	}
	return glfwWindowShouldClose(m_glfwWindow);
}

void Window::Present()
{
	glfwSwapBuffers(m_glfwWindow);
}

Window::~Window()
{
	glfwDestroyWindow(m_glfwWindow);
}
