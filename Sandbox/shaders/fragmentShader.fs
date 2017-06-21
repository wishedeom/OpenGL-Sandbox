#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Colours
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Attenuation
{
	float constant;
	float linear;
	float quadratic;
};

struct DirectionalLight
{
	vec3 direction;
	Colours colours;
};

struct PointLight
{
	vec3 position;
	Attenuation attenuation;
	Colours colours;
};

in vec3 fragPos;
in vec3 vNormal;
in vec2 vTexture;

out vec4 fColour;

uniform vec3 viewPos;
uniform Material material;
uniform DirectionalLight directionalLight;

vec3 directionalLightColour(DirectionalLight light);
vec3 pointLightColour(PointLight light);
float computeAttenutation(Attenuation a, float distance);

void main()
{        
    fColour = vec4(directionalLightColour(directionalLight), 1.0f);
}

vec3 directionalLightColour(DirectionalLight light)
{
	vec3 direction = normalize(-light.direction);
	float diff = max(dot(vNormal, direction), 0.0f);
	vec3 reflection = reflect(-direction, vNormal);
	float spec = pow(max(dot(fragPos - viewPos, reflection), 0.0f), material.shininess);
	
	vec3 ambient = light.colours.ambient * vec3(texture(material.diffuse, vTexture));
	vec3 diffuse = light.colours.diffuse * diff * vec3(texture(material.diffuse, vTexture));
	vec3 specular = light.colours.specular * spec * vec3(texture(material.specular, vTexture));
	
	return ambient + diffuse + specular;
}

vec3 pointLightColour(PointLight light)
{
	vec3 direction = normalize(light.position - fragPos);
	float diff = max(dot(vNormal, direction), 0.0f);
	vec3 reflection = reflect(-direction, vNormal);
	float spec = pow(max(dot(fragPos - viewPos, reflection), 0.0f), material.shininess);
	float distance = length(light.position - fragPos);
	float attenuation = computeAttenutation(light.attenuation, distance);

	vec3 ambient = light.colours.ambient * vec3(texture(material.diffuse, vTexture));
	vec3 diffuse = light.colours.diffuse * diff * vec3(texture(material.diffuse, vTexture));
	vec3 specular = light.colours.specular * spec * vec3(texture(material.specular, vTexture));

	return (ambient + diffuse + specular) * attenuation;
}

float computeAttenutation(Attenuation a, float distance)
{
	return 1.0f / (a.constant + (a.linear + a.quadratic * distance) * distance);
}
