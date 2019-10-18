#include "entity.h"
#include "component.h"

void Entity::tick()
{
	for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); it++)
	{
		(*it)->onTick();
	}
}

void Entity::display()
{
}

std::shared_ptr<Engine> Entity::getEngine()
{
	return engine.lock();
}

