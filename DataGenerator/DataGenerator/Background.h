#ifndef BACKGROUND_H
#define BACKGROUND_H

#define _USE_MATH_DEFINES

#include <string>
#include <vector>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TextureService.h"
#include "Shader.h"
#include "Camera.h"

enum TextureType
{
	Wall,
	Floor
};

class Background
{
public:

	Background(float maxModelDimention);

	Background() {};

	void AddTexture(const char *path, const string &directory, TextureType type);

	void SetPosition(float width, float height, Camera camera, float scale, float offsetAngle, glm::vec3 globalUp = glm::vec3(0.0f, 0.0f, -1.0f));

	void SetTexture(unsigned int id, TextureType type);

	void Draw(Shader Shader);

private:
	//OpenGL congig
	unsigned int VBO, VAO, EBO;

	float *Vertices;

	TextureService TextureService;

	//Texture IDs  and types
	vector<unsigned int> TexturesWall;
	vector<unsigned int> TexturesFloor;
	unsigned int TextureId;
	TextureType Type;

	//Helpers
	glm::mat4 Transformation;
	float MaxModelDimention;

	float get2VectorAngleXY(glm::vec3 vec, glm::vec3 vec2);
	void Setup();
};

#endif