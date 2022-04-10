#pragma once

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target)
{
	CameraPosition = position;
	Target = target;
	WorldUp = glm::vec3(0.0f, 0.0f, -1.0f);

	updateCameraVectors();
}

void Camera::Set(glm::vec3 position, glm::vec3 target)
{
	CameraPosition = position;
	Target = target;

	Zoom = 45;

	updateCameraVectors();
}

void Camera::Describe()
{
	std::cout << "Pos: " << glm::to_string(CameraPosition) << std::endl;
	std::cout << "Target: " << glm::to_string(Target) << std::endl;
	std::cout << "Direction: " << glm::to_string(CameraDirection) << std::endl;
	std::cout << "Up: " << glm::to_string(CameraUp) << std::endl;
	std::cout << "Right: " << glm::to_string(CameraRight) << std::endl;
}

void Camera::updateCameraVectors()
{
	CameraDirection = glm::normalize(Target - CameraPosition);
	CameraRight = glm::normalize(glm::cross(CameraDirection, WorldUp));
	CameraUp = glm::normalize(glm::cross(CameraDirection, CameraRight));
};

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(CameraPosition, Target, CameraUp);
}