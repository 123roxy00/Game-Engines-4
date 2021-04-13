#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class LightSource
{
private:
	glm::vec3 position;
	glm::vec3 lColour;
	float ambient;
	float diffuse;
	float specular;

public:
	LightSource();
	~LightSource();

	const glm::vec3 GetPosition() { return position; }
	const glm::vec3 GetLColour() { return lColour; }
	const float GetAmbient() { return ambient; }
	const float GetDiffuse() { return diffuse; }
	const float GetSpecular() { return specular; }
	
	void SetPosition(glm::vec3 position_);
	void SetLColour(glm::vec3 lColour_);
	void SetAmbient(float ambient_);
	void SetDiffuse(float diffuse_);
	void SetSpecular(float specular_);
};

#endif // LIGHTSOURCE_H