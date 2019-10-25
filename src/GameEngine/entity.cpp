#include "entity.h"
#include "component.h"

void Entity::tick()
{
	for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); it++)
	{
		(*it)->onTick();
		std::cout << "Components updated" << std::endl;
	}
}

void Entity::display()
{
	for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); it++)
	{
		(*it)->onDisplay();
		std::cout << "Components updated" << std::endl;
	}
}

std::shared_ptr<Engine> Entity::getEngine()
{
	return engine.lock();
}

