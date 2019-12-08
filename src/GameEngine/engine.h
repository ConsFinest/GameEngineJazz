#ifndef _ENGINE_H_
#define _ENGINE_H_


#include <iostream>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <rend/rend.h>
#include <fstream>


#include <stb_image/stb_image.h>

#include "component.h"
#include "audioSource.h"
#include "camera.h"
#include "transform.h"
#include "entity.h"


class Camera;
class Entity; //forward declare

class Engine
{

public: 
	
	std::weak_ptr<Engine> self;
	~Engine();
	static std::sr1::shared_ptr<Engine> intialize();
	std::shared_ptr<Entity> addEntity();
	void start();
	void stop();
	std::sr1::shared_ptr<rend::Context> getContext();
	std::sr1::shared_ptr<rend::Context> context;
	std::sr1::weak_ptr<Camera> currentCam;
	//To do make camera vector private
	std::vector<std::sr1::weak_ptr<Camera>> cameras;


private: 
	std::vector<std::shared_ptr<Entity>> entities;
	bool running;
	SDL_Window *window;
	ALCdevice* device;
	ALCcontext* ALcontext;
	
};


#endif // !_ENGINE_H_
