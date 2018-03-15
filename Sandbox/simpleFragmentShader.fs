#version 330 core

in vec3 fragPos;

out vec4 fColour;

void main()
{
	fColour = vec4(2.0f * fragPos, 1.0f);
}
