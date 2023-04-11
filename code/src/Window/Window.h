#pragma once
#include <string>


class DisplaySystem;

class Window {
protected:
	struct AccessKey;
public:
	MHTL::public_signal_t<void(int key, int scancode, int action, int mods), AccessKey> sig_onKeyEvent;

private:
	GLFWwindow* m_glfwWindow;
	static void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	void OnKeyEvent(int key, int scancode, int action, int mods);
public:
	Window(GLFWwindow* m_glfwWindow);
	bool ShouldClose();
	void Present();
	~Window();
};