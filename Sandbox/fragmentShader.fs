#version 330 core

in vec3 vColour;
in vec2 vTex;

out vec4 fColour;

uniform sampler2D uTexture;

void main()
{
	fColour = texture(uTexture, vTex);
}
