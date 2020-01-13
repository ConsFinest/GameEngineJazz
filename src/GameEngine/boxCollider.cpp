#include "boxCollider.h"
#include "entity.h"
#include "transform.h"
#include "engine.h"

void boxCollider::onTick()
{
	onCollideBox();
	//std::cout << "updated col box" << std::endl;
}

void boxCollider::onCollideBox()
{
	std::vector<std::shared_ptr<Entity> > bces;
	bces = getEngine()->getEntities<boxCollider>();

	glm::vec3 np = getEntity()->getComponent<Transform>()->getPos() + offset;

	for (std::vector<std::shared_ptr<Entity>>::iterator it = bces.begin(); it != bces.end(); it++)
	{
		if (*it == getEntity())
		{
			continue;
		}
		
			std::shared_ptr<boxCollider> bc = (*it)->getComponent<boxCollider>();
			//TODO stop objects being pushed
			if (bc->getMoveable())
			{
				glm::vec3 sp = bc->collisionResponse(np, size);
				np = sp;
				np = np - offset;
				getEntity()->getComponent<Transform>()->setPos(np);
				lastPosition = np;
			}
	}
}

void boxCollider::setMoveable(bool _set)
{
	moveable = _set;
}

bool boxCollider::getMoveable()
{
	return moveable;
}

void boxCollider::onInit()
{
	size = glm::vec3(1, 1, 1);
	lastPosition = getEntity()->getComponent<Transform>()->getPos();
	
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
	glm::vec3 a = getEntity()->getComponent<Transform>()->getPos() + offset;
	glm::vec3& as = this->size;
	glm::vec3& b = _pos;
	glm::vec3& bs = _size;

	if (a.x > b.x) // a right of b
	{
		if (a.x - as.x > b.x + bs.x) // left edge of a greater than right edge of b (not colliding)
		{
			return false;
		}
	}
	else
	{
		if (b.x - bs.x > a.x + as.x)
		{
			return false;
		}
	}

	if (a.z > b.z) // a front of b
	{
		if (a.z - as.z > b.z + bs.z) // back edge of a greater than front edge of b (not colliding)
		{
			return false;
		}
	}
	else
	{
		if (b.z - bs.z > a.z + as.z)
		{
			return false;
		}
	}

	if (a.y > b.y) // a above b
	{
		if (a.y - as.y > b.y + bs.y) // bottom edge of a greater than top edge of b (not colliding)
		{
			return false;
		}
	}
	else
	{
		if (b.y - bs.y > a.y + as.y)
		{
			return false;
		}
	}

	return true;


}

glm::vec3 boxCollider::collisionResponse(glm::vec3 _pos, glm::vec3 _size)
{
	float amount = 0.1f;
	float step = 0.1f;

	while (true)
	{
		if (!isColliding(_pos, _size)) break;
		_pos.x += amount;
		if (!isColliding(_pos, _size)) break;
		_pos.x -= amount;
		_pos.x -= amount;
		if (!isColliding(_pos, _size)) break;
		_pos.x += amount;
		_pos.z += amount;
		if (!isColliding(_pos, _size)) break;
		_pos.z -= amount;
		_pos.z -= amount;
		if (!isColliding(_pos, _size)) break;
		_pos.z += amount;
		_pos.y += amount;
		if (!isColliding(_pos, _size)) break;
		_pos.y -= amount;
		_pos.y -= amount;
		if (!isColliding(_pos, size)) break;
		_pos.y += amount;
		amount += step;
	}

	return _pos;
}

