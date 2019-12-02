#include "camera.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 760

glm::vec3 Camera::getPos()
{
	return camPos;
}

glm::mat4 Camera::getView()
{
	/*glm::mat4 model(1.0f);
	viewMat = glm::translate(model, camPos);
	viewMat = glm::rotate(viewMat, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));*/
	std::sr1::shared_ptr<Entity> ent = getEntity();
	std::sr1::shared_ptr<Transform> transform = ent->getComponent<Transform>();
	
	return transform->getModel();
}

glm::mat4 Camera::getProj()
{
	projMat = glm::perspective(glm::radians(angle), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.0f);
	return projMat;
}

void Camera::cameraInit(float _angle)
{
	angle = _angle;
	camPos = glm::vec3(0, 0, 0);
	std::sr1::shared_ptr<Entity> ent = getEntity();
	std::sr1::shared_ptr<Transform> transform = ent->getComponent<Transform>();
	camPos = transform->getPos();
}
