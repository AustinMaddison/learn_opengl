#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void frame_buffer_size_callback(GLFWwindow* window, int height, int width);
void process_input(GLFWwindow* window);

// Triangle
// --------
float vertices[] =
{	// vertex postion		vertex color
	-0.5f,  -0.5f,  0.0f,	1.0f, 0.0f, 0.0f,
	 0.5f,  -0.5f,  0.0f,	0.0f, 1.0f, 0.0f,
	 0.0f,   0.5f,  0.0f,	0.0f, 0.0f, 1.0f
};

int main()
{
	// initialize and configure GLFW
	// -----------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create GLFW window
	// ------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello, Window!", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

	// glad: load all opengl functions
	// -------------------------------

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to intialize GLAD!" << std::endl;
		glfwTerminate();
		return -1;
	}



	// Max number of vertex attributes supported
	// -----------------------------------------
	int nrAtrributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAtrributes);
	std::cout << "Max number of vertex attributes supported: " << nrAtrributes << std::endl;

	Shader vertexColorShader("vertex_shader.vert", "fragment_shader.frag");

	// Generate and bind VAO, VBO
	// --------------------------
	unsigned int VAO, VBO;
	
	glGenVertexArrays(1, &VAO);  
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Set vertex attribute pointer (for the VAO to access VBO)
	// --------------------------------------------------------
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);  
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3)); // we have to offset by 12 strides
	glEnableVertexAttribArray(1);



	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		process_input(window);

		// render
		glClearColor(0.2f, 0.2f, 0.4f, 1.0f);  // sets what color glClear should use to clear buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw triangle
		// -------------
		vertexColorShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// swap buffer and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// terminate glfw, clearing all allocated memory
	// ---------------------------------------------
	glfwTerminate();
	return 0;
}

// glfw: queries if relevant keys are pressed and reacts accordingly
// -----------------------------------------------------------------
void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

// glfw: when user changes the dimensions of the window, this callback function executes
// -------------------------------------------------------------------------------------
void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
	// ensures opengl viewport dimensions match dimensions of window
	glViewport(0, 0, width, height);
}

