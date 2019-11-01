#include "transform.h"

void Transform::setPos(glm::vec3 _Pos)
{
	Position = _Pos;
}

glm::vec3 Transform::getPos()
{
	return Position;
}

void Transform::setRot(glm::vec3 _Rot)
{
	Rotation = _Rot;
}

glm::vec3 Transform::getRot()
{
	return Rotation;
}

void Transform::setScale(glm::vec3 _Scale)
{
	Scale = _Scale;
}

glm::vec3 Transform::getScale()
{
	return Scale;
}
