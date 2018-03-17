#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 colour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 worldPosition;
out vec3 vNormal;
out vec3 vColour;

void main()
{
	worldPosition = vec3(model * vec4(position, 1.0f));
	vNormal = vec3(transpose(inverse(model)) * vec4(normalize(normal), 0.0f));
	vColour = colour;
	gl_Position  =  projection * view * model * vec4(position, 1.0);
}
