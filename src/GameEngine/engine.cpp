#include "engine.h"
#include "entity.h"
#include "input.h"


#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 760

Engine::~Engine()
{
	for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		entities.erase(it);
	}
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
	eng->deltaTime = 0;
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
	//init context
	eng->context = rend::Context::initialize();
	//init inputmanager
	eng->input = Input::init();
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

std::shared_ptr<Entity> Engine::addCamera(glm::vec3 _pos, bool _setCurrent, int _angle)
{
	std::shared_ptr<Entity>ent = std::make_shared<Entity>();
	entities.push_back(ent);
	ent->engine = self;
	ent->self = ent;
	std::shared_ptr<Transform>trans = ent->addComponent<Transform>();
	trans->setPos(_pos);
	std::shared_ptr<Camera>cam = ent->addComponent<Camera>();
	if (_setCurrent)
	{
		cam->setCurrent();
	}
	cam->playerControll(true);
	cam->cameraInit(_angle);
	return ent;
}

void Engine::start()
{
	
	running = true;
	
	lastTime = SDL_GetTicks();
	int i =0;
	while (running)
	{
		
		//DELTATIME
		timeT = SDL_GetTicks();
		float diff = timeT - lastTime;
		deltaTime = diff / 1000.0f;
		lastTime = timeT;
		float idealTime = 1.0f / 60.0f;
		if (idealTime > deltaTime)
		{
			SDL_Delay((idealTime - deltaTime)*1000.0f);
		}


		glClearColor(0.10f, 0.15f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SDL_Event event = { 0 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			switch(event.type)
			{
			case SDL_KEYDOWN:
				//std::cout << "keypress" << std::endl;
				input->addKey(event.key.keysym.scancode);
				break;
			case SDL_KEYUP:
				input->removeKey(event.key.keysym.scancode);
				break;
			default:
				break;
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				if (!firstMouse)
				{
					input->setMousePos(event.motion.xrel, event.motion.yrel);
				}
				else
				{
					firstMouse = false;
					input->setMousePos(0, 0);
				}
			}
			if (input->keyPressed(SDL_SCANCODE_EQUALS) && delay < 0) //prevents skipping to last camera
			{
				nextCam();
				delay = 20; 
			}
			if (input->keyPressed(SDL_SCANCODE_MINUS) && delay < 0)
			{
				prevCam();
				delay = 20;
			}
		}
		
		for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
		{
			(*it)->tick();
			
		}
		for (std::vector<std::weak_ptr<Camera>>::iterator camIt = cameras.begin(); camIt != cameras.end(); camIt++)
		{
			//TODO work this out 
			currentCam = getCurrentCam();

			for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
			{
				(*it)->display();
			}
		}
		input->onTick();
		SDL_GL_SwapWindow(window);
		delay--;
	}

}


void Engine::stop()
{
	running = false;
}

std::sr1::shared_ptr<rend::Context> Engine::getContext()
{
	return context;
}

float Engine::getDeltaTime()
{
	return deltaTime;
}

SDL_Window * Engine::getWindow()
{
	return window;
}

std::weak_ptr<Camera> Engine::getCurrentCam()
{
	for (auto it = cameras.begin(); it != cameras.end(); it++)
	{
		if ((*it).lock()->getCurrent())
		{
			return *it;
		}
	}
}

void Engine::nextCam()
{
	bool cam = false;
	for (auto it = cameras.begin(); it != cameras.end(); it++)
	{
		if (cam)
		{
			(*it).lock()->setCurrent();
			return;
		}
		if ((*it).lock()->getCurrent())
		{
			cam = true;
		}
	}
}

void Engine::prevCam()
{
	bool cam = false;
	for (auto it = cameras.begin(); it != cameras.end();it++)
	{
		if ((*it).lock()->getCurrent())
		{
			cam = true;
			if(it != cameras.begin())
			{
				it--;
			}
			(*it).lock()->setCurrent();
			return;
		}
	}
}

std::shared_ptr<Input> Engine::getInput()
{
	return input;
}


	








