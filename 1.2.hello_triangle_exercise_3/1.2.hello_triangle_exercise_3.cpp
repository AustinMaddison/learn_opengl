
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void frame_buffer_size_callback(GLFWwindow* window, int height, int width);
void process_input(GLFWwindow* window);

float vertices_a[] =
{
	// first triangle
	-0.50f,   0.50f,  0.0f,
	-0.10f,  -0.50f,  0.0f,
	-0.90f,  -0.50f,  0.0f,
};

float vertices_b[] =
{
	// second triangle
	 0.50f,  0.50f,  0.0f,
	 0.90f, -0.50f,  0.0f,
	 0.10f, -0.50f,  0.0f
};

// Shaders
// -------
const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos, 1.0);\n"
	"}\0";

const char* fragmentShaderSourceYellow = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0, 1.0, 0.0, 1.0);"
	"}\0";

const char* fragmentShaderSourceMagenta = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0, 0.0, 1.0, 1.0);"
	"}\0";


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

	// Shaders : Removed error checking for better readibility of the process
	// ----------------------------------------------------------------------
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int fragmentShaderMagenta = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int shaderProgramYellow = glCreateProgram();
	unsigned int shaderProgramMagenta = glCreateProgram();

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
	glCompileShader(fragmentShaderYellow);

	glShaderSource(fragmentShaderMagenta, 1, &fragmentShaderSourceMagenta, NULL);
	glCompileShader(fragmentShaderMagenta);

	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);  

	glAttachShader(shaderProgramMagenta, vertexShader);
	glAttachShader(shaderProgramMagenta, fragmentShaderMagenta);
	glLinkProgram(shaderProgramMagenta);


	// delete shader objects, no longer need them
	// ------------------------------------------
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderYellow);
	glDeleteShader(fragmentShaderMagenta);

	// ------------------------------
	// Generate and bind VAOs, VBOs
	// ------------------------------
	unsigned int VAOs[2], VBOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	

	// FIRST TRIANGLE
	// --------------
	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_a), vertices_a, GL_STATIC_DRAW); 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);  
	glEnableVertexAttribArray(0);  
	
	// SECOND TRIANGLE
	// ---------------
	glBindVertexArray(VAOs[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_b), vertices_b, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		process_input(window);

		//render
		glClearColor(0.2f, 0.2f, 0.4f, 1.0f);  // sets what color glClear should use to clear buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// activate shader programm, bind VAO and draw
		// -----------------------
		// std::cout << "draw" << std::endl;
		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAOs[0]);	// first triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgramMagenta);
		glBindVertexArray(VBOs[1]); // second triangle
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

