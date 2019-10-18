#ifndef  _COMPONENT_H_
#define _COMPONENT_H_

#include <memory>
#include <vector>

class Entity;
class Engine;

class Component
{
	Component();
	~Component();
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
