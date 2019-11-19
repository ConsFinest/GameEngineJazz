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
	std::sr1::shared_ptr<rend::Shader> createShader(const std::string &source);
	std::sr1::shared_ptr<rend::Mesh> createMesh(const std::string _loc);
	std::sr1::shared_ptr<rend::Texture> createTexture(const std::string _loc);

private: 
	std::vector<std::shared_ptr<Entity>> entities;
	bool running;
	SDL_Window *window;
	std::sr1::shared_ptr<rend::Context> context;
};


#endif // !_ENGINE_H_
