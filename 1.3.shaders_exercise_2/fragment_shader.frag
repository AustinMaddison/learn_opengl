#version 330

uniform float uTime;

in vec3 vertexColor;
out vec4 fragColor;

void main()
{
	fragColor = vec4(vertexColor, 1.0);
}