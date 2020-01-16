#include "physics.h"
#include "boxCollider.h"

Physics::Physics()
{
	kinematic = true;
	first = false;
	gravity = 9.81;
}

void Physics::onTick()
{
	std::shared_ptr<Engine> eng = getEngine();
	std::shared_ptr<Entity> ent = getEntity();
	if (kinematic)
	{
		glm::vec3 pos = ent->getComponent<Transform>()->getPos();
		
		glm::vec3 acc = glm::vec3(0, -gravity, 0);
		if (ent->getComponent<Transform>()->getPos().y - 4 < 0)
		{
			addVelocity(-vel);
		}
		if (ent->getComponent<Transform>()->getPos().y > 0)
		{
			gravity = 9.81;
		}

		glm::vec3 v = vel + (acc * (eng->getDeltaTime() / 50));
		
	    setVelocity(v);
		
		ent->getComponent<Transform>()->setPos((pos += vel));
		std::cout << getVelocity().y << std::endl;
	}
}

void Physics::setVelocity(glm::vec3 _vel)
{
	vel = _vel;
}

void Physics::addVelocity(glm::vec3 _vel)
{
	vel += _vel;
}

void Physics::setKinematic(bool _set)
{
	kinematic = _set;
}

bool Physics::getKinematic()
{
	return kinematic;
}

glm::vec3 Physics::getVelocity()
{
	return vel;
}

void Physics::setGravity(float _value)
{
	gravity = _value;
}

void Physics::reduceGravity(float _value)
{
	if (gravity > 0)
	{
		gravity -= _value;
	}
}
