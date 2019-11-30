#include "camera.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 760

glm::mat4 Camera::getView()
{
	return viewMat;
}

glm::mat4 Camera::getProj()
{
	projMat = glm::perspective(glm::radians(angle), 1.0f, 0.1f, 100.0f);
	return projMat;
}

void Camera::cameraInit(float _angle)
{
	angle = _angle;
	pos = glm::mat4(1.0f);
}
