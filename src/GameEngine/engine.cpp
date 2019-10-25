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
	while (true)
	{
		for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
		{
			(*it)->tick();
			std::cout << "Entity updated" << std::endl;
		}
		for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
		{
			(*it)->display();
			std::cout << "Entity Drawns" << std::endl;
		}
	}

}

void Engine::stop()
{
	running = false;
}


