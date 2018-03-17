#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 colour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vColour;

void main()
{
	vColour = vec4(colour, 1.0f);
	gl_Position  =  projection * view * model * vec4(position, 1.0);
}
