#ifndef _ENGINE_H_
#define _ENGINE_H_


#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 760

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
class boxCollider;
class Input;


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
	float getDeltaTime();
	SDL_Window* getWindow();

	std::weak_ptr<Camera> getCurrentCam();
	
	void nextCam();
	void prevCam();
	std::sr1::weak_ptr<Camera> currentCam;
	//To do make camera vector private
	std::vector<std::sr1::weak_ptr<Camera>> cameras;

	std::shared_ptr<Input> getInput();


	template<class T> 
	std::vector < std::shared_ptr<Entity>> getEntities()
	{
		std::vector<std::shared_ptr<Entity>> ents;
		for (auto it = entities.begin(); it != entities.end(); it++)
		{
			bool add = (*it)->searchComponents<T>();
			if (add)
			{
				ents.push_back(*it);
				//std::cout << "type :" << typeid(T).name() << " found" << std::endl;
			}
		}
		return ents;
	}


private: 

	std::sr1::shared_ptr<rend::Context> context;

	std::vector<std::shared_ptr<Entity>> entities;
	std::shared_ptr<Input> input;
	bool running;
	SDL_Window *window;
	ALCdevice* device;
	ALCcontext* ALcontext;
	float deltaTime;
	float lastTime;
	float timeT;
	bool firstMouse;
	
};


#endif // !_ENGINE_H_

