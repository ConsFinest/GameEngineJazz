#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "component.h"
#include "engine.h"

class Camera : public Component
{
	glm::vec3 camPos;
	glm::mat4 viewMat;
	glm::mat4 projMat;
	float angle;
public:
	glm::vec3 getPos();
	glm::mat4 getView();
	glm::mat4 getProj();
	void cameraInit(float _angle);

};





#endif // !_CAMERA_H_
