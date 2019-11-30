#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "component.h"

class Camera : public Component
{
	glm::mat4 pos;
	glm::mat4 viewMat;
	glm::mat4 projMat;
	float angle;
public:

	glm::mat4 getView();
	glm::mat4 getProj();
	void cameraInit(float _angle);

};





#endif // !_CAMERA_H_
