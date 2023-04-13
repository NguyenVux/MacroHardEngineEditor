#pragma once
#include "Window/Window.h"
#include "Graphic/ShaderProgram.h"
class GLFWApplication {
protected:
	struct AccessKey;
private:
	std::shared_ptr<Window> m_window;
	fteng::connection m_keyEventConnection;
	Graphic::ShaderProgram m_shaderProgram;
public:
	void Update(float dt);
	void Start();
	void OnKeyEvent(int key, int scancode, int action, int mods);
	GLFWApplication(std::shared_ptr<Window> i_window);
	~GLFWApplication();
};
