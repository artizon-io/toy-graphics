#include <iostream>
// #include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "shader.h"


static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	std::cout << "Window resized" << std::endl;
}

static void processInput(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

static void RenderLoop(GLFWwindow* window, unsigned int VAO, Shader shader) {
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// Clear color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader.ID); 
		glBindVertexArray(VAO);

		// Uniform
		float timeValue = glfwGetTime();
		std::cout << timeValue << std::endl;
		float blueColorValue = sin(timeValue) / 4.0f + 0.75f;
		unsigned int vertexColorLocation = glGetUniformLocation(shader.ID, "blueColor");
		glUniform1f(vertexColorLocation, blueColorValue);

		// With EBO (drawing a rectangle)
		// Draw mode; no. indicies; type of indicies; offset
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Double buffering
		glfwSwapBuffers(window);

		// Process events e.g. keyboard
		glfwPollEvents();
	}

	glfwTerminate();
}

int main(void)
{
	GLFWwindow* window;

	// Initialise GLFW
	if (!glfwInit()) {
		std::cout << "Failed to initialised GLFW" << std::endl;
		return -1;
	}

	// Version 4.1 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create window
	window = glfwCreateWindow(640, 480, "Toy OpenGL", NULL, NULL);
	if (!window) {
		glfwTerminate();
		std::cout << "Failed to create window" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialise GLEW
	// if (GLEW_OK != glewInit())
	// 	std::cout << "Error" << std::endl;

	// Initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl
;		return -1;
	}

	float vertexData[] = {
		 // position   // color
		 0.5f,  0.5f,  0.2f, 0.3f, 0.8f,  // top right
		 0.5f, -0.5f,  0.4f, 0.8f, 0.4f,  // bottom right
		-0.5f, -0.5f,  0.7f, 0.6f, 0.8f,  // bottom left
		-0.5f,  0.5f,  0.9f, 0.4f, 0.6f,  // top left
	};

	// VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * (2 + 3) * sizeof(float), vertexData, GL_STATIC_DRAW);

	// 0th vertex attrib; 2 GL_FLOAT; not normalised; stride; no offset (require weird cast)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, (2 + 3) * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 1st vertex attrib; 3 GL_FLOAT; not normalised; stride; no offset (require weird cast)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (2 + 3) * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// EBO
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Shader
	Shader shader = Shader("shader/vertex.vs", "shader/fragment.fs");

	RenderLoop(window, VAO, shader);

	return 0;
}