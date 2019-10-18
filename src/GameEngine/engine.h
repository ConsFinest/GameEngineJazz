#ifndef _ENGINE_H_
#define _ENGINE_H_


#include <memory>
#include <vector>

class Entity; //forward declare

class Engine
{
	Engine();
	~Engine();

public: 
	static std::shared_ptr<Engine> intialize();
	std::shared_ptr<Entity> addEntity();
	void start();
	void stop();

private: 
	std::vector<std::shared_ptr<Entity>> entities;
	bool running;
};


#endif // !_ENGINE_H_
