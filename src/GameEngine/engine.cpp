#include "engine.h"
#include "entity.h"


std::shared_ptr<Engine> Engine::intialize()
{
	std::shared_ptr<Engine>eng = std::make_shared<Engine>();
	eng->self = eng;
	return eng;
}

std::shared_ptr<Entity> Engine::addEntity()
{
	std::shared_ptr<Entity>ent = std::make_shared<Entity>();
	entities.push_back(ent);
	ent->engine = self;
	ent->self = ent;
	return ent;
}

void Engine::start()
{
	running = true;
	while (running)
	{
		SDL_Event event = { 0 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}
		
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


