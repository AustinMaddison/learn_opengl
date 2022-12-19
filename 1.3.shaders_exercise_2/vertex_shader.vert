#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float uTime;
uniform float uOffsetX;

out vec3 vertexColor;

void main()
{
	vertexColor = aColor;
	gl_Position = vec4(aPos.x + uOffsetX, aPos.y, aPos.z, 1.0);
}