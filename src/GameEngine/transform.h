#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "component.h"


class Transform : public Component
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

public:
	void setPos(glm::vec3 _Pos);
	glm::vec3 getPos();
	void setRot(glm::vec3 _Rot);
	glm::vec3 getRot();
	void setScale(glm::vec3 _Scale);
	glm::vec3 getScale();
};




#endif // !_TRANSFORM_H_
