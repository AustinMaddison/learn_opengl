#version 330

uniform float uTime;

in vec3 vertexPosition;
in vec3 vertexColor;
out vec4 fragColor;

void main()
{
	fragColor = vec4(vertexPosition, 1.0);
}