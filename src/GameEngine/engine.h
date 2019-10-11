#ifndef _ENGINE_H_
#define _ENGINE_H_


#include <memory>

class Entity;

class Engine
{
	Engine();
	~Engine();

public: 
	static std::shared_ptr<Engine> intialize();
	std::shared_ptr<Entity> addEntity();
	void start();
	void stop();
};


#endif // !_ENGINE_H_
