#ifndef  _COMPONENT_H_
#define _COMPONENT_H_

#include <iostream>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Entity;
class Engine;

class Component
{
	friend Entity;
	friend Engine;

	std::weak_ptr<Engine> engine;
	std::weak_ptr<Entity> entity;
	virtual void onInit();
	virtual void onBegin();
	virtual void onTick();
	virtual void onDisplay();
	
public:
	std::shared_ptr<Entity>getEntity();
	std::shared_ptr<Engine>getEngine();
};





#endif // ! _COMPONENT_H_
