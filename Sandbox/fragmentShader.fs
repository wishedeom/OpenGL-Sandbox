#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fragPos;
in vec3 vNormal;
in vec2 vTexture;

out vec4 fColour;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	vec3 diffuseTex = vec3(texture(material.diffuse, vTexture));

    // Ambient
    vec3 ambient = light.ambient * diffuseTex;

    // Diffuse 
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseTex;
    
    // Specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, vTexture));
        
    vec3 result = ambient + diffuse + specular;
    fColour = vec4(result, 1.0f);
}
