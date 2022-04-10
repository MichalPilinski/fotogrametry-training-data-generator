#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include "glm/ext.hpp"

#include <vector>

class Camera
{
public:
	
	glm::vec3 CameraPosition;
	glm::vec3 Target;
	glm::vec3 CameraDirection;
	glm::vec3 CameraUp;
	glm::vec3 CameraRight;
	glm::vec3 WorldUp;

	float Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f));

	void Set(glm::vec3 position, glm::vec3 target);

	glm::mat4 GetViewMatrix();

	void Describe();

private:

	void updateCameraVectors();

};
#endif