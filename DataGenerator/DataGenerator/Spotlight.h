#ifndef LIGHT_SPOTLIGHT_H
#define LIGHT_SPOTLIGHT_H

#include "Light.h"

class SpotLight : public Light
{
public:
	SpotLight() {};

	SpotLight(Shader lightShader, Shader lampShader , glm::vec3 direction, glm::vec3 position = glm::vec3(0, 0, 0), float cutOff = 12.5f, float outterCutOff = 15.0f) : Light(position, lightShader, lampShader)
	{
		Direction = direction;
		CutOff = cutOff;
		OuterCutOff = outterCutOff;
	};

	void SetUniform() override;
	void SetDirection(glm::vec3 direction);

private:
	glm::vec3 Direction;
	float CutOff;
	float OuterCutOff;
};

#endif