#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "component.h"

class Camera : public Component
{
	glm::mat4 viewMat;
	glm::mat4 projMat;

public:
	glm::mat4 getView();
	glm::mat4 getProj();

};





#endif // !_CAMERA_H_
