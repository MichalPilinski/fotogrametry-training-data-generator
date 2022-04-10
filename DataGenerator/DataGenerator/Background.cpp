#pragma once

#include "Background.h"



Background::Background(float maxModelDimention)
{
	MaxModelDimention = maxModelDimention;
	Setup();
}

void Background::AddTexture(const char *path, const string &directory, TextureType type) 
{
	unsigned int TextureId = TextureService.TextureFromFile(path, directory, false, true);
	if (type == Wall)
	{
		TexturesWall.push_back(TextureId);
	}
	else if (type == Floor)
	{
		TexturesFloor.push_back(TextureId);
	}
}

void Background::SetTexture(unsigned int id, TextureType type) 
{
	Type = type;
	if (type == Wall && TexturesWall.size() < id) 
	{
		id = TexturesWall.size() - 1;
	}
	else if (TexturesFloor.size() < id)
	{
		id = TexturesFloor.size() - 1;
	}

	TextureId = id;
}

void Background::SetPosition(float maxHeight, float screenRatio, Camera camera, float scale, float offsetAngle, glm::vec3 globalUp)
{
	//angles and translations calculation
	glm::vec3 cameraDirXY = camera.CameraDirection;
	cameraDirXY.z = 0;
	cameraDirXY = glm::normalize(cameraDirXY);

	glm::vec3 Normal(0, 1, 0);

	float Angle = get2VectorAngleXY(glm::vec3(0, 1, 0), cameraDirXY);
	float WallDistance = MaxModelDimention / 2 * 1.2f;

	Transformation = glm::mat4();

	// translations
	if (Type == Wall) 
	{
		Transformation = glm::translate(Transformation, -1 * globalUp * scale);
		Transformation = glm::translate(Transformation, cameraDirXY * MaxModelDimention/2 * 1.2);
	}
	else Transformation = glm::translate(Transformation, -1 * cameraDirXY * scale / 2);

	// rotations
	Transformation = glm::rotate(Transformation, (float)(offsetAngle / 180 * M_PI), globalUp);

	if(Type == Floor) Transformation = glm::rotate(Transformation, 3.1415f / 2, glm::cross(cameraDirXY, globalUp));
	Transformation = glm::rotate(Transformation, (float)(Angle - 3.1415f/2), globalUp);

	//scaling
	if (Type == Wall) Transformation = glm::scale(Transformation, glm::vec3(scale));
	else Transformation = glm::scale(Transformation, glm::vec3(scale));
}

void Background::Setup() 
{
	float vertices[] = {
		  0.0f,  1.0f,  1.0f, 1.0f, 1.0f, // top right
		  0.0f,  1.0f, -1.0f, 1.0f, 0.0f, // bottom right
		  0.0f, -1.0f, -1.0f, 0.0f, 0.0f, // bottom left
		  0.0f, -1.0f,  1.0f, 0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO);
	cout << VAO;
	glGenBuffers(1, &VBO);
	cout << VBO;
	glGenBuffers(1, &EBO);
	cout << EBO << endl;

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);
}

void Background::Draw(Shader Shader)
{
	Shader.use();
	Shader.setMat4("model", Transformation);
	unsigned int Texture = Type == Wall ? TexturesWall[TextureId] : TexturesFloor[TextureId];

	glActiveTexture(GL_TEXTURE0);
	
	Shader.setInt("texture_diffuse" + std::to_string(Texture), Texture);

	glBindTexture(GL_TEXTURE_2D, Texture);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

float Background::get2VectorAngleXY(glm::vec3 vec, glm::vec3 vec2)
{
	float Dot = vec.x * vec2.x + vec.y * vec2.y;
	float Det = vec.x * vec2.y + vec.y * vec2.x;
	return atan2(Det, Dot);
}