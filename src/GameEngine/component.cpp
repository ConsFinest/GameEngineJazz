#include "component.h"

Component::Component()
{
}

Component::~Component()
{
}

void Component::onInit()
{
}

void Component::onBegin()
{
}

void Component::onTick()
{
}

void Component::onDisplay()
{
}

std::shared_ptr<Entity> Component::getEntity()
{
	return std::shared_ptr<Entity>();
}

std::shared_ptr<Engine> Component::getEngine()
{
	return std::shared_ptr<Engine>();
}
