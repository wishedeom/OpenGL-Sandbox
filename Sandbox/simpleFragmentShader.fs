#version 330 core

out vec4 fColour;

in vec4 vColour;

uniform float ambientLightStrength;
uniform vec3 ambientLightColour;

void main()
{
	fColour = vColour * ambientLightColour * ambientLightStrength;
}
