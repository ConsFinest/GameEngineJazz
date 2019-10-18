#ifndef  _COMPONENT_H_
#define _COMPONENT_H_

#include <iostream>
#include <memory>
#include <vector>

class Entity;
class Engine;

class Component
{
	friend Entity;
	std::weak_ptr<Entity> entity;
	void onInit();
	void onBegin();
	void onTick();
	void onDisplay();
	
public:
	std::shared_ptr<Entity>getEntity();
	std::shared_ptr<Engine>getEngine();

};





#endif // ! _COMPONENT_H_
