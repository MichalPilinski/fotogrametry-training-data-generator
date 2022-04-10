#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

class Light
{
public:
	Light() {};

	Light(glm::vec3 position, Shader lightShader, Shader lampShader);

	void SetVectors(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void SetScalars(float constant, float linear, float quadratic);
	void SetPosition(glm::vec3 position);

	virtual void SetUniform() = 0;

	void Draw();

protected:
	unsigned int VBO, CubeVAO;
	unsigned int LightVAO;
	float *Vertices;

	glm::vec3 Position;
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;

	float Constant;
	float Linear;
	float Quadratic;

	Shader LightShader;
	Shader LampShader;

	void ConfigureBuffers();
	void SetupVertices();
};

#endif