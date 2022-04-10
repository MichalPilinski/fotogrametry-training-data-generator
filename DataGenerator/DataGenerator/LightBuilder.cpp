#pragma once

#include "LightsBuilder.h"

void LightsBuilder::SetScalars(float constant, float linear, float quadratic)
{
	Constant = constant;
	Linear = linear;
	Quadratic = quadratic;
}

void LightsBuilder::SetVectors(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	Ambient = ambient;
	Diffuse = diffuse;
	Specular = specular;
}

void LightsBuilder::AddPoint(glm::vec3 position)
{
	PointLight Light(LightShader, LampShader, position);
	Light.SetScalars(Constant, Linear, Quadratic);
	Light.SetVectors(Ambient, Diffuse, Specular);

	PointLightSources.push_back(Light);
}

void LightsBuilder::AddDirectional(glm::vec3 direction)
{
	DirectLight Light(LightShader, LampShader, direction);
	Light.SetVectors(Ambient, Diffuse, Specular);

	DirectionLightSource = Light;
	IsDirectional = true;
}

void LightsBuilder::AddSpot(glm::vec3 position, glm::vec3 direction, float cutOff, float outterCutOff)
{
	SpotLight Light(LightShader, LampShader, direction, position, cutOff, outterCutOff);
	Light.SetScalars(Constant, Linear, Quadratic);
	Light.SetVectors(Ambient, Diffuse, Specular);

	SpotLightSource = Light;
	IsSpot = true;
}

void LightsBuilder::Draw()
{
	
}

void LightsBuilder::SetDirectional(glm::vec3 direction)
{
	DirectionLightSource.SetDirection(direction);
}

void LightsBuilder::DisableDirectional()
{
	IsDirectional = false;
}

void LightsBuilder::SetSpot(glm::vec3 position, glm::vec3 direction)
{
	SpotLightSource.SetDirection(direction);
	SpotLightSource.SetPosition(position);
}

void LightsBuilder::DisableSpot() 
{
	IsSpot = false;
}

void LightsBuilder::SetPoint(int id, glm::vec3 position)
{
	if (id < PointLightSources.size)
	{
		PointLightSources[id].SetPosition(position);
	}
}

void LightsBuilder::DeletePoint(int id)
{
	if (id < PointLightSources.size)
	{
		PointLightSources.erase(PointLightSources.begin() + id);
	}
}

void LightsBuilder::ClearPoints()
{
	PointLightSources.clear();
}