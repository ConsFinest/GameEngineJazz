#include "component.h"
void Component::onInit()
{
}

void Component::onBegin()
{
}

void Component::onTick()
{
	std::cout << "Component Update finished" << std::endl;
}

void Component::onDisplay()
{
	std::cout << "Components Drawn" << std::endl; 
}

std::shared_ptr<Entity> Component::getEntity()
{
	return entity.lock();
}

std::shared_ptr<Engine> Component::getEngine()
{
	return engine.lock();
}
