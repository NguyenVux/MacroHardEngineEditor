#include <memory>
#include "GLFWApplication.h"
#include <iostream>
#include <fstream>
#include "Graphic/GlHelpers.h"
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
	auto pos = m_shaderProgram.GetUniformLocation("z");
	float z = (glm::sin(glfwGetTime())+1)*3;
	
	glUniform1f(pos, z);
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
	glm::mat4 projectionMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

	// Use the projectionMatrix in your OpenGL code, e.g. pass it to the shader
	m_shaderProgram.Use();
	auto pos = m_shaderProgram.GetUniformLocation("projectionMatrix");
	glUniformMatrix4fv(pos, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	auto erro = glGetError();
	if (erro != GL_NO_ERROR)
	{
		LOG_INFO("No Error", "GRAPHIC");
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