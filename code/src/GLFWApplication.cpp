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
	Graphic::ShaderProgram sProg;
	{
		auto v = Graphic::Shader::CreateShader("../../../../data/VertexShader.glsl", Graphic::ShaderType::VertexShader);
		auto s = Graphic::Shader::CreateShader("../../../../data/FragmentShader.glsl", Graphic::ShaderType::FragmentShader);
		if (v != MHTL::success)
		{
			LOG_ERROR(v.error().what(), "GLFWApplication");
			m_window->Close();
			return;
		}
		if (s != MHTL::success)
		{
			LOG_ERROR(s.error().what(), "GLFWApplication");
			m_window->Close();
			return;
		}
		sProg.AttachShader(v.extract_payload());
		sProg.AttachShader(s.extract_payload());
		auto r = sProg.LinkProgram();
		if (r != MHTL::success)
		{
			LOG_ERROR(r.error().what(), "GLFWApplication");
			m_window->Close();
			return;
		}
	}
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