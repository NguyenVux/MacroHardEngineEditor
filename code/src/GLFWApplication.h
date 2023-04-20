#pragma once
#include "Window/Window.h"
#include "Graphic/ShaderProgram.h"
#include "Graphic/Camera.h"

class GLFWApplication {
protected:
	struct AccessKey;
private:
	std::shared_ptr<Window> m_window;
	fteng::connection m_keyEventConnection;
	Graphic::ShaderProgram m_shaderProgram;
	Graphic::Camera m_mainCam;
	GLuint VAO,VBO,EBO;

public:
	void Update(float dt);
	void Start();
	void OnKeyEvent(int key, int scancode, int action, int mods);
	GLFWApplication(std::shared_ptr<Window> i_window);
	~GLFWApplication();
};
