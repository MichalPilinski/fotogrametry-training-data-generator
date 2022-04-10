#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"
#include <string>

class PointLight : public Light
{
public:
	PointLight() {};

	PointLight(Shader lightShader, Shader lampShader, glm::vec3 position = glm::vec3(0, 0, 0)) : Light(position, lightShader, lampShader)
	{
		if(LightsNumber < 3) LightsNumber++;
	}

	void SetUniform() override;

private:
	static int LightsNumber;

	std::string EnumerateString(const char* start, const char* end);
};

#endif