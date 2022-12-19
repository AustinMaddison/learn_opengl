#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	std::string vShaderCode;
	std::string fShaderCode;

	// configure ifstream
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit); // ensures that ifstream can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		vShaderFile.open(vertexPath);
		vShaderFile.open(fragmentPath);

		std::stringstream vShaderStream;
		std::stringstream fShaderStream;
		
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderCode = vShaderStream.str();
		fShaderCode = fShaderStream.str();
		
		// convert strings to cstrings for opengl
		const char* vShaderSrc = vShaderCode.c_str();
		const char* fShaderSrc = fShaderCode.c_str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FAILED_TO_READ_SHADER_SOURCE_FILES: " << e.what() << std::endl;
	}
	
	// create shaders and compile
	int unsigned vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	errorCheck(vertexShader, "VERTEX");
	errorCheck(fragmentShader, "FRAGMENT");

	// create shader program and link
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	errorCheck(ID, "PROGRAM");
}

void Shader::addUniformInt(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::addUniformFloat(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}
	
void Shader::addUniformBool(const char* name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void Shader::useShader()
{
	glUseProgram(ID);
}

void Shader::errorCheck(unsigned int shaderID, const char* type)
{
	int success;
	char infoLog[512];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << type << "::COMPILE_FAILED:\n" << infoLog << '\n' << "-- --------------------------------- --";
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << type << "::LINKER_FAILED:\n" << infoLog << '\n' << "-- --------------------------------- --";
		}
	}
}


