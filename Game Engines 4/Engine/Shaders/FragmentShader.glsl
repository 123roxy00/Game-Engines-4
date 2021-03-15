#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

uniform sampler2D inputTexture;
uniform vec3 viewPosition;

out vec4 fColour;

struct Light
{
	vec3 Position;
	float Ambient;
	float Diffuse;
	float Specular;
	vec3 Colour;
};

uniform Light light;

void main()
{

	vec3 ambient = light.Ambient * texture(inputTexture, TexCoords).rgb * light.Colour;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.Position - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * light.Diffuse) * texture(inputTexture, TexCoords).rgb * light.Colour;
	
	vec3 viewDir = normalize(viewPosition - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = (spec * light.Specular) * light.Colour;

	vec3 result = ambient + diffuse + specular;
	
	fColour = vec4(result, 1.0f);
}

