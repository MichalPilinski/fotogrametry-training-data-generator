#pragma once

#include "Spotlight.h"

void SpotLight::SetUniform()
{
	LightShader.use();
	LightShader.setVec3("spotLight.position", Position);
	LightShader.setVec3("spotLight.direction", Direction);
	LightShader.setVec3("spotLight.ambient", Ambient);
	LightShader.setVec3("spotLight.diffuse", Diffuse);
	LightShader.setVec3("spotLight.specular", Specular);
	LightShader.setFloat("spotLight.constant", Constant);
	LightShader.setFloat("spotLight.linear", Linear);
	LightShader.setFloat("spotLight.quadratic", Quadratic);
	LightShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(CutOff)));
	LightShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(OuterCutOff)));
}

void SpotLight::SetDirection(glm::vec3 direction) 
{
	Direction = direction;
}