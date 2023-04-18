#include "Window.h"
#include <iostream>
void Window::OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	win->OnKeyEvent(key, scancode, action, mods);
}

void Window::OnResolutionChange(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	win->OnKeyEvent(key, scancode, action, mods);
}



void Window::OnKeyEvent(int key, int scancode, int action, int mods)
{
	MHTL::access<AccessKey>(sig_onKeyEvent).emit(key, scancode, action, mods);
}

Window::Window(GLFWwindow* i_window): m_glfwWindow(i_window)
{
	glfwSetWindowUserPointer(m_glfwWindow, this);
	glfwSetKeyCallback(m_glfwWindow, &Window::OnKeyEvent);
	
}

bool Window::ShouldClose()
{
	if (m_glfwWindow == nullptr)
	{
		return true;
	}
	return glfwWindowShouldClose(m_glfwWindow);
}

WindowSize Window::GetWindowSize()
{
	int width;
	int height;
	glfwGetWindowSize(m_glfwWindow,&width,&height);
	WindowSize size = {
		width,
		height
	};
	return size;
}

void Window::Close()
{
	glfwSetWindowShouldClose(m_glfwWindow, 1);
}

void Window::Present()
{
	if (m_glfwWindow == nullptr)
	{
		return;
	}
	glfwSwapBuffers(m_glfwWindow);
}

Window::~Window()
{
	glfwDestroyWindow(m_glfwWindow);
}
