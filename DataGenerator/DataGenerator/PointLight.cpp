#pragma once

#include "PointLight.h"

int PointLight::LightsNumber = 0;

void PointLight::SetUniform()
{
	LightShader.use();
	LightShader.setVec3(EnumerateString("pointLights[", "].position"), Position);
	LightShader.setVec3(EnumerateString("pointLights[", "].ambient"), Ambient);
	LightShader.setVec3(EnumerateString("pointLights[", "].diffuse"), Diffuse);
	LightShader.setVec3(EnumerateString("pointLights[", "].specular"), Specular);
	LightShader.setFloat(EnumerateString("pointLights[", "].constant"), Constant);
	LightShader.setFloat(EnumerateString("pointLights[", "].linear"), Linear);
	LightShader.setFloat(EnumerateString("pointLights[", "].quadratic"), Quadratic);
}

std::string PointLight::EnumerateString(const char* start, const char* end)
{
	std::string Output;

	Output += start;
	Output += LightsNumber;
	Output += end;

	return Output;
}