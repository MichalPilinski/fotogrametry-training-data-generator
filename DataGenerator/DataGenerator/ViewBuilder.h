#pragma once
#define _USE_MATH_DEFINES

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

#include <iostream>
#include <ctime>

#include "Background.h"

#define DEBUG

using namespace glm;

class ViewBuilder
{
public:

	// dividers as { distance, height, angle }
	// config as {Min Dist Modifier, Min Height Modifier, 
	ViewBuilder(glm::vec3 modelBoundingBox, float maxDistanceFactor, float maxHeightFactor, glm::vec3 dividers, float cameraFOV);

	glm::vec3 GetCameraPosition();
	glm::vec3 GetCameraTarget();


	void Describe();

private:
	//main funcs
	bool NextView();

	//Camera positioning
	glm::vec3 ModelBoundingBox;
	glm::vec3 Dividers;

	double MinDistance, MinHeight;
	double MaxDistance, MaxHeight;

	double CurrentAngle, CurrentDistance, CurrentHeight;

	float CameraFOV;

	float RandomizeDist(float val);
	float GetPerspectiveLength(glm::vec3 boundingBox);

	//Background operations

	const char **TexturesPathArray;

	Background BackgroundProvider;



};