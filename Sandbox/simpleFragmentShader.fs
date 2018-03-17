#version 330 core

out vec4 fColour;

in vec4 vColour;

void main()
{
	fColour = vColour;
}
