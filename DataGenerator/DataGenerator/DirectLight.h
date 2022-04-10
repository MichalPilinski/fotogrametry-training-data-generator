#ifndef LIGHT_DIFFUSE_H
#define LIGHT_DIFFUSE_H

#include "Light.h"

class DirectLight : public Light
{
public:
	DirectLight() {};

	DirectLight(Shader lightShader, Shader lampShader, glm::vec3 direction, glm::vec3 position = glm::vec3(0,0,0)) : Light(position, lightShader, lampShader)
	{
		Direction = direction;
	};
		
	void SetUniform() override;

	void SetDirection(glm::vec3 direction);

private:
	glm::vec3 Direction;
};

#endif