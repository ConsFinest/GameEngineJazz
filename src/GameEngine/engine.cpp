#include "engine.h"
#include "entity.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

Engine::~Engine()
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(ALcontext);
	alcCloseDevice(device);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

std::shared_ptr<Engine> Engine::intialize()
{
	std::shared_ptr<Engine>eng = std::make_shared<Engine>();
	eng->self = eng;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw rend::Exception("SDL FAILED TO INITIALISE");
	}

	eng->window = SDL_CreateWindow("Lab 4 - Architecture",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(eng->window))
	{
		throw rend::Exception("OPENGL CONTEXT FAILED TO INITIALISE");
	}

	//ALCcreation

	eng->device = alcOpenDevice(NULL);
	if (eng->device == NULL)
	{
		throw rend::Exception("OPENAL FAILED TO INITIALISE");
	}
	eng->ALcontext = alcCreateContext(eng->device, NULL);
	if (eng->ALcontext == NULL)
	{
		alcCloseDevice(eng->device);
		throw rend::Exception("ALCONTEXT FAILED TO INITIALISE");
	}
	if (!alcMakeContextCurrent(eng->ALcontext))
	{
		alcDestroyContext(eng->ALcontext);
		alcCloseDevice(eng->device);
		throw rend::Exception("CONTEXT NOT MADE CURRENT");
	}
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	eng->context = rend::Context::initialize();

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
		}
		for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
		{
			(*it)->display();
		}
		SDL_GL_SwapWindow(window);
	}

}

void Engine::stop()
{
	running = false;
}

std::sr1::shared_ptr<rend::Context> Engine::getContext()
{
	return std::sr1::shared_ptr<rend::Context>();
}




