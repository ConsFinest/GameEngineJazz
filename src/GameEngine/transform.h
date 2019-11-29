#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "component.h"


class Transform : public Component
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

public:
	Transform();
	Transform(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale);
	void setPos(glm::vec3 _Pos);
	void setRot(glm::vec3 _Rot);
	void setScale(glm::vec3 _Scale);

	glm::vec3 getRot();
	glm::vec3 getPos();
	glm::vec3 getScale();
	glm::mat4 getModel();

	void addRot(glm::vec3 _rot);
	void addTrans(glm::vec3 _trans);
};




#endif // !_TRANSFORM_H_
