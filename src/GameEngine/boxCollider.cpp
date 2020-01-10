#include "boxCollider.h"
#include "entity.h"
#include "transform.h"

void boxCollider::onTick()
{

}

void boxCollider::onInit()
{
	size = glm::vec3(1, 1, 1);
	position = getEntity()->getComponent<Transform>()->getPos();
	
}

void boxCollider::setSize(glm::vec3 size)
{
	this->size = size;
}

void boxCollider::setOffset(glm::vec3 _offset)
{
	this->size = offset;
}

bool boxCollider::isColliding(glm::vec3 _pos, glm::vec3 _size)
{
	return false;
}

glm::vec3 boxCollider::collisionResponse(glm::vec3 _pos, glm::vec3 _size)
{
	return glm::vec3();
}
