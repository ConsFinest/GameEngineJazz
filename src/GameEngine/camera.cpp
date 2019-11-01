#include "camera.h"

glm::mat4 Camera::getView()
{
	return viewMat;
}

glm::mat4 Camera::getProj()
{
	return projMat;
}
