#version 330 core

in vec2 vTex;

out vec4 fColour;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

void main()
{
	fColour = mix(texture(uTexture0, vTex), texture(uTexture1, vTex), 0.5);
}
