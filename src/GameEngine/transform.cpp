#include "transform.h"

Transform::Transform()
{
	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);
}

Transform::Transform(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale)
{
	Position = _pos;
	Rotation = _rot;
	Scale = _scale;
}

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

glm::mat4 Transform::getModel()
{
	glm::mat4 Model(glm::mat4(1.0f)); 
	Model = glm::rotate(Model, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
	Model = glm::rotate(Model, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
	Model =	glm::rotate(Model, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
	Model = glm::translate(Model, Position);
	Model = glm::scale(Model, Scale);
	return Model;

}

void Transform::addRot(glm::vec3 _rot)
{
	Rotation += _rot;
}

void Transform::addTrans(glm::vec3 _trans)
{
	glm::mat4 Model = getModel();
	glm::vec4 res = Model * glm::vec4(_trans, 1.0f);
	Position = glm::vec3(res);
}


