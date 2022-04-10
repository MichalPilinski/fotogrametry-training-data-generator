#pragma once

#include "ViewBuilder.h"

ViewBuilder::ViewBuilder(vec3 modelBoundingBox, float maxDistanceFactor, float maxHeightFactor, vec3 dividers, float cameraFOV)
{
	ModelBoundingBox = modelBoundingBox;

	Dividers = dividers;

	MinDistance = glm::max(modelBoundingBox.x, modelBoundingBox.y) * 0.8;
	MinHeight = modelBoundingBox.z * 0.8;

	MaxDistance = MinDistance * maxDistanceFactor;
	MaxHeight = MinHeight * maxHeightFactor;

	CurrentAngle = 0;
	CurrentDistance = MinDistance;
	CurrentHeight = MinHeight;

	CameraFOV = cameraFOV;

	std::srand((int)std::time(nullptr));
}

glm::vec3 ViewBuilder::GetCameraPosition()
{
	double CameraX = cos(CurrentAngle)*CurrentDistance;
	double CameraY = sin(CurrentAngle)*CurrentDistance;

	double CameraZ = CurrentHeight;

	return glm::vec3(CameraX, CameraY, CameraZ);
}

glm::vec3 ViewBuilder::GetCameraTarget()
{	
	NextView();

	glm::vec3 Target;

	float maxDeflection = GetPerspectiveLength(ModelBoundingBox);
		
	#ifndef DEBUG
	Target.x = RandomizeDist(maxDeflection);
	Target.y = RandomizeDist(maxDeflection);
	Target.z = RandomizeDist(maxDeflection);
	#endif

	#ifdef DEBUG
	Target.x = 0;
	Target.y = 0;
	Target.z = 0;
	#endif

	return Target;
}

void ViewBuilder::Describe()
{
	std::cout << "Current distance: " << CurrentDistance << ", Max distance: " << MaxDistance << std::endl;
	std::cout << "Current angle: " << CurrentAngle << ", Max angle: " << 2 * M_PI << std::endl;
	std::cout << "Current height: " << CurrentHeight << ", Max height: " << MaxHeight << std::endl;
}

bool ViewBuilder::NextView()
{
	CurrentAngle += 2 * M_PI / Dividers.z;
	if (CurrentAngle > 2 * M_PI)
	{
		CurrentAngle = 0;
		CurrentHeight += (MaxHeight - MinHeight) / Dividers.y;

		if (CurrentHeight > MaxHeight) {
			CurrentHeight = MinHeight;
			CurrentDistance += (MaxDistance - MinDistance) / Dividers.x;

			if (CurrentDistance > MaxDistance) return false; //all views generated
		}
	}

	return false;
}

float ViewBuilder::RandomizeDist(float val)
{
	return (std::rand() % (int)(val * 100)) / 100 - val / 2;
}

float ViewBuilder::GetPerspectiveLength(glm::vec3 boundingBox)
{
	glm::vec3 halfBounding(boundingBox.x / 2, boundingBox.y / 2, boundingBox.z / 2);

	float length = std::sqrt(halfBounding.x*halfBounding.x + halfBounding.y*halfBounding.y + halfBounding.z*halfBounding.z);

	return length / cos(radians(CameraFOV));
}