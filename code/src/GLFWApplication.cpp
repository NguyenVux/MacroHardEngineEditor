#include <memory>
#include "GLFWApplication.h"
#include <iostream>
#include <fstream>
const std::string s_rootPath = "..\\..\\..\\..\\";


void GLFWApplication::Update(float dt)
{
}

void GLFWApplication::Start()
{
	LOG_INFO("Application Start", "GLFWApplication");
}

void GLFWApplication::OnKeyEvent(int key, int scancode, int action, int mods)
{
}

GLFWApplication::GLFWApplication(std::shared_ptr<Window> i_window) : m_window(i_window)
{
	LOG_INFO("Creating Application", "GLFWApplication");
	m_keyEventConnection = m_window->sig_onKeyEvent.connect<&GLFWApplication::OnKeyEvent>(this);
}

GLFWApplication::~GLFWApplication() {
	glfwTerminate();
	LOG_INFO("Application Destroy", "GLFWApplication");
}