#ifndef LIGHTS_BUILDER_H
#define LIGHTS_BUILDER_H

#include <vector>

#include "Shader.h";
#include "DirectLight.h";
#include "PointLight.h";
#include "SpotLight.h";

class LightsBuilder 
{
public:
	LightsBuilder(Shader lightShader, Shader lampShader)
	{
		LightShader = lightShader;
		LampShader = lampShader;

		IsSpot = false;
		IsDirectional = false;
	}

	void SetScalars(float constant, float linear, float quadratic);

	void SetVectors(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

	void AddDirectional(glm::vec3 direction);

	void AddPoint(glm::vec3 position);

	void AddSpot(glm::vec3 position, glm::vec3 direction, float cutOff = 12.5f, float outterCutOff = 15.0f);

	void SetDirectional(glm::vec3 direction);

	void DisableDirectional();

	void SetSpot(glm::vec3 position, glm::vec3 direction);

	void DisableSpot();

	void SetPoint(int id, glm::vec3 position);

	void DeletePoint(int id);

	void ClearPoints();

	void Draw();

private:
	Shader LightShader;
	Shader LampShader;

	std::vector<PointLight> PointLightSources;
	DirectLight DirectionLightSource;
	SpotLight SpotLightSource;

	bool IsDirectional;
	bool IsSpot;
	
	glm::vec3 Ambient;
	glm::vec3 Specular;
	glm::vec3 Diffuse;

	float Constant;
	float Linear;
	float Quadratic;
};

#endif