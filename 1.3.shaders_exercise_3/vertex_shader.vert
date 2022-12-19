#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float uTime;
uniform float uOffsetX;

out vec3 vertexColor;
out vec3 vertexPosition;

void main()
{	
	vertexColor = aColor;
	vertexPosition = aPos;
	gl_Position = vec4(aPos, 1.0);
}