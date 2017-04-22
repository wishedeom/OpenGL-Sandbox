#version 330 core

in vec3 vColour;
in vec2 vTex;

out vec4 fColour;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

void main()
{
	fColour = mix(texture(uTexture0, vTex), texture(uTexture1, vTex), 0.5) * vec4(vColour, 1.0f);
	//fColour = texture(uTexture0, vTex);
}
