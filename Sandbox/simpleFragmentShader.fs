#version 330 core

out vec4 fColour;

in vec3 worldPosition;
in vec3 vNormal;
in vec3 vColour;

uniform float ambientLightStrength;
uniform vec3 ambientLightColour;

uniform vec3 lightColour;
uniform vec3 lightPosition;

void main()
{
	// Diffuse
	vec3 lightDirection = normalize(lightPosition - worldPosition);
	float diffuseFactor = max(dot(vNormal, lightDirection), 0.0f);
	vec3 diffuseColour = diffuseFactor * lightColour;

	fColour = vec4(vColour, 1.0f) * (ambientLightColour * ambientLightStrength + diffuseColour);
}
