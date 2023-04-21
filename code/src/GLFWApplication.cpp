#include <memory>
#include "GLFWApplication.h"
#include <iostream>
#include <fstream>
#include "Graphic/GlHelpers.h"
#include "glm/gtx/quaternion.hpp"
const std::string s_rootPath = "..\\..\\..\\..\\";

// Define the vertices of the cube
	static std::array<glm::vec3, 8> cube = {
		glm::vec3(-0.5f, -0.5f, -0.5f), // Vertex 0
		glm::vec3(0.5f, -0.5f, -0.5f),  // Vertex 1
		glm::vec3(0.5f, 0.5f, -0.5f),   // Vertex 2
		glm::vec3(-0.5f, 0.5f, -0.5f),  // Vertex 3
		glm::vec3(-0.5f, -0.5f, 0.5f),  // Vertex 4
		glm::vec3(0.5f, -0.5f, 0.5f),   // Vertex 5
		glm::vec3(0.5f, 0.5f, 0.5f),    // Vertex 6
		glm::vec3(-0.5f, 0.5f, 0.5f)    // Vertex 7
	};



	// Define the faces of the cube using vertex indices
	static std::array<GLuint, 3 * 12> faces = {
		0, 1, 2,0, 2, 3, // Front face
		1, 5, 6,1, 6, 2, // Right face
		5, 4, 7,5, 7, 6, // Back face
		4, 0, 3,4, 3, 7, // Left face
		3, 2, 6,3, 6, 7, // Top face
		4, 5, 1,4, 1, 0  // Bottom face
	};

void GLFWApplication::Update(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(VAO);
	m_shaderProgram.Use();
	GLint prjPos = m_shaderProgram.GetUniformLocation("projectionMatrix");
	GLint mPos = m_shaderProgram.GetUniformLocation("ModelMatrix");

	//auto modelMatrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 0.0f, -3.0f))* glm::toMat4(glm::qua<float>(glm::radians(glm::highp_vec3(0, glm::sin(glfwGetTime()) * 360 ,0))));
	auto modelMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,10.f));
	//auto viewMatrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 0.0f,-3.0f)) * glm::toMat4(glm::qua<float>(glm::radians(glm::highp_vec3(glm::sin(glfwGetTime()/100)*360,0,0))));
	/*m_mainCam.rotate(glm::vec3(0.0f, 0.0f, 0.0f));*/
	glUniformMatrix4fv(prjPos, 1, GL_FALSE, glm::value_ptr(m_mainCam.getMatrix()));
	glUniformMatrix4fv(mPos, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_INT, 0);

	m_window->Present();
}

void GLFWApplication::Start()
{
	LOG_INFO("Application Start", "GLFWApplication");
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
		m_shaderProgram.AttachShader(v.extract_payload());
		m_shaderProgram.AttachShader(s.extract_payload());
		auto r = m_shaderProgram.LinkProgram();
		if (r != MHTL::success)
		{
			LOG_ERROR(r.error().what(), "GLFWApplication");
			m_window->Close();
			return;
		}
	}
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Field of view (FOV) in radians
	constexpr float fov = glm::radians(70.0f);

	// Aspect ratio (width / height)
	WindowSize size = m_window->GetWindowSize();
	float aspectRatio = static_cast<float>(size.width)/size.height;

	// Near and far clipping planes
	float nearPlane = 0.1f;
	float farPlane = 100000.0f;

	// Create perspective projection matrix
	m_mainCam.setProjectionMatrix(fov, aspectRatio, nearPlane, farPlane);
	m_mainCam.setPosition(glm::vec3(0.0f, 0.0f, 9.0f));
	m_mainCam.setRotation(glm::vec3(0.0f,0.0f,0.0f));
	//m_mainCam.LookAt(glm::vec3(-35.f, 0.f, 0.f));
	// Use the projectionMatrix in your OpenGL code, e.g. pass it to the shader
	m_shaderProgram.Use();
	

	auto erro = glGetError();
	if (erro != GL_NO_ERROR)
	{
		LOG_INFO("No Error", "GRAPHIC");
	}
}

void GLFWApplication::OnKeyEvent(int key, int scancode, int action, int mods)
{
	glm::vec3 rot(0.0f);
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {

		rot.x = 3.0f;
	}	
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {

		rot.x = -3.0f;
	}	
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {

		rot.y = 3.0f;
	}	
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		rot.y = -3.0f;
	}
	m_mainCam.rotate(rot);


	glm::vec3 dir(0.0f);
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {

		dir.z = 1.0f;
	}	
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {

		dir.z = -1.0f;
	}	
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {

		dir.x = -1.0f;
	}	
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		dir.x = 1.0f;
	}
	m_mainCam.translate(dir);
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