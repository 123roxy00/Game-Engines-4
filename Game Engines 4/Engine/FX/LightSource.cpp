#include "LightSource.h"

LightSource::LightSource() : position(glm::vec3()), ambient(0.0f),
	diffuse(0.0f), specular(0.0f), lColour(glm::vec3())
{

}

LightSource::~LightSource()
{
}

void LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::SetLColour(glm::vec3 lColour_)
{
	lColour = lColour_;
}

void LightSource::SetAmbient(float ambient_)
{
	ambient = ambient_;
}

void LightSource::SetDiffuse(float diffuse_)
{
	diffuse = diffuse_;
}

void LightSource::SetSpecular(float specular_)
{
	specular = specular_;
}