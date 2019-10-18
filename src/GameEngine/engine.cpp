#include "engine.h"
#include "entity.h"


std::shared_ptr<Engine> Engine::intialize()
{
	std::shared_ptr<Engine>eng = std::make_shared<Engine>();
	return eng;
}

std::shared_ptr<Entity> Engine::addEntity()
{
	std::shared_ptr<Entity>ent = std::make_shared<Entity>();
	entities.push_back(ent);
	return ent;
}

void Engine::start()
{
	for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		//(*it)->addComponent<Component>();
		(*it)->tick();
	}
}

void Engine::stop()
{
}


