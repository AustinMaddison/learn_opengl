#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <glad/glad.h>

class Shader
{
	unsigned int ID;

public:
	Shader(const char* vertexPath, const char* fragmentPath);
	
	void addUniformInt(const char* name, int value);
	void addUniformFloat(const char* name, float value);
	void addUniformBool(const char* name, bool value);
	
	void useShader();

private:
	void errorCheck(unsigned int shaderID, const char* type);
};

