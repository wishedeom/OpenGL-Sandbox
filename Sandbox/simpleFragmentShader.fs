#version 330 core

out vec4 fColour;

in vec3 worldPosition;
in vec3 vNormal;
in vec3 vColour;

uniform float ambientLightStrength;
uniform vec3 ambientLightColour;

uniform vec3 lightColour;
uniform vec3 lightPosition;

uniform vec3 viewPosition;

void main()
{
	// Diffuse
	vec3 lightDirection = normalize(lightPosition - worldPosition);
	float diffuseFactor = max(dot(vNormal, lightDirection), 0.0f);
	vec3 diffuseColour = diffuseFactor * lightColour;

	// Specular
	vec3 viewDirection = normalize(worldPosition - viewPosition);
	vec3 reflectedDirection = reflect (-lightDirection, vNormal);
	float specularFactor = pow(max(dot(viewDirection, reflectedDirection), 0.0f), 32);
	vec3 specularColour = specularFactor * lightColour * 0.5;

	fColour = vec4(vColour, 1.0f) * (ambientLightColour * ambientLightStrength + diffuseColour);
}
