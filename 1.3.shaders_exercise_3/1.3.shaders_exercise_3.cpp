#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

// window
const int SCR_WIDTH{ 800 };
const int SCR_HEIGHT{ 600 };	
const char* WINDOW_NAME{ "recall_exercise" };

// triangle
const float vertices[]
{	// vertex position  // vertex color
	 0.0,  0.5, 0.0,	1.0, 0.0, 0.0,
	-0.5, -0.5, 0.0,	0.0, 1.0, 0.0,
	 0.5, -0.5, 0.0,	0.0, 0.0, 1.0
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

int main()
{
	// init and configure glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// create window
	GLFWwindow* window;
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// load glad 
	gladLoadGL();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load GLAD!" << std::endl;
	}

	// print info
	std::string vendorName = reinterpret_cast<const char*>(glGetString(GL_VENDOR)) ;
	std::string rendererName = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	std::cout << vendorName + ' ' + rendererName << std::endl;

	int nrAttribute;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttribute);
	std::cout << "Maximum vertex attributes : " << nrAttribute << std::endl;

	// Shaders
	// -------
	Shader newShader = Shader("vertex_shader.vert", "fragment_shader.frag");

	// generate and bind VAO and VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// you need to bind the Vertex Array Object to set vertex buffers
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// configure vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)(sizeof(float)*3));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);

		glClearColor(0.25, 0.3, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		newShader.addUniformFloat("uTime", glfwGetTime());
		newShader.addUniformFloat("uOffsetX", 0.5);


		glBindVertexArray(VAO);
		newShader.useShader();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
