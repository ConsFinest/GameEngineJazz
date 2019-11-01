#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <iostream>
#include <memory>
#include <vector>
#include "component.h"

class Entity; //forward declare

class Engine
{

public: 
	std::weak_ptr<Engine> self;
	static std::shared_ptr<Engine> intialize();
	std::shared_ptr<Entity> addEntity();
	void start();
	void stop();

private: 
	std::vector<std::shared_ptr<Entity>> entities;
	bool running;
};


#endif // !_ENGINE_H_
