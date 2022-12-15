#include "Shader.h"

Shader::Shader(const char* vertexSrcPath, const char* fragmentSrcPath)
{
	// Read shader source files
	// ------------------------
	std::string vShaderCode;
	std::string fShaderCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open file
		vShaderFile.open(vertexSrcPath);
		fShaderFile.open(fragmentSrcPath);
		// read's file's buffer contents into streams
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into strings
		vShaderCode = vShaderStream.str();
		fShaderCode = fShaderStream.str();

	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FAILED_TO_READ_FILE" << std::endl;
	}
	// convert strings to c strings
	const char* vShaderSrc = vShaderCode.c_str();
	const char* fShaderSrc = fShaderCode.c_str();


	unsigned int vertexShader, fragmentShader;
	
	// Initialize shader and program
	// -----------------------------
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	ID = glCreateProgram();
	
	// Attatch Shader Source and Compile
	// ---------------------------------
	glShaderSource(vertexShader, 1, &vShaderSrc, NULL);
	glShaderSource(fragmentShader, 1, &fShaderSrc, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	
	// Check for compile errors
	// ------------------------
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::use()
{
	glUseProgram(ID);
}
