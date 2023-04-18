#pragma once
#include <string>


class DisplaySystem;
struct WindowSize {
	int width;
	int height;
};
class Window {
protected:
	struct AccessKey;
public:
	MHTL::public_signal_t<void(int key, int scancode, int action, int mods), AccessKey> sig_onKeyEvent;
	//MHTL::public_signal_t<void(int key, int scancode, int action, int mods), AccessKey> sig_onKeyEvent;

private:
	GLFWwindow* m_glfwWindow;
	static void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void OnResolutionChange(GLFWwindow* window, int key, int scancode, int action, int mods);
	void OnKeyEvent(int key, int scancode, int action, int mods);
public:
	Window(GLFWwindow* m_glfwWindow);
	bool ShouldClose();
	WindowSize GetWindowSize();
	void Close();
	void Present();
	~Window();
};