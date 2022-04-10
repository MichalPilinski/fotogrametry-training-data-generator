#pragma once

#include "DirectLight.h"

void DirectLight::SetUniform()
{
	LightShader.use();
	LightShader.setVec3("dirLight.direction", Direction.x, Direction.y, Direction.z);
	LightShader.setVec3("dirLight.ambient", Ambient);
	LightShader.setVec3("dirLight.diffuse", Diffuse);
	LightShader.setVec3("dirLight.specular", Specular);
}

void DirectLight::SetDirection(glm::vec3 direction)
{
	Direction = direction;
}