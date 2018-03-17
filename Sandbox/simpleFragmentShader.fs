#version 330 core

out vec4 fColour;

in vec4 vColour;

uniform vec3 lightColour;

void main()
{
	fColour = vColour * lightColour;
}
