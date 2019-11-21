#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <rend/rend.h>
#include <iostream>
#include <memory>
#include <vector>

class Engine;
class Component;



class Entity
{
	friend Engine;

	std::weak_ptr<Engine> engine;
	std::weak_ptr<Entity> self;
	std::vector<std::shared_ptr<Component>> components;
	void tick();
	void display();
	
public:
	//template dont need ;
	//template perameter forwarding - LOOK UP 
	std::shared_ptr<Engine> getEngine();
	template<class T> 
	std::shared_ptr<T> addComponent() {
		std::shared_ptr<T>rtn = std::make_shared<T>();
		components.push_back(rtn);
		rtn->entity = self;
		rtn->engine = engine;
		return rtn;
	}
	template<class T, class A>
	std::shared_ptr<T> addComponent(A a) {
		std::shared_ptr<T>rtn = std::make_shared<T>(a);
		components.push_back(rtn);
		rtn->entity = self;
		rtn->engine = engine;
		return rtn;
	}
	template<class T, class A, class B>
	std::shared_ptr<T> addComponent(A a, B b) {
		std::shared_ptr<T>rtn = std::make_shared<T>(a,b);
		components.push_back(rtn);
		rtn->entity = self;
		rtn->engine = engine;
		return rtn;
	}
	template<class T, class A, class B, class C>
	std::shared_ptr<T> addComponent(A a, B b, C c) {
		std::shared_ptr<T>rtn = std::make_shared<T>(a,b,c);
		components.push_back(rtn);
		rtn->entity = self;
		rtn->engine = engine;
		return rtn;
	}

	template<class T>
	std::shared_ptr<T>GetComponent()
	{
		for (auto it = components.begin(); it != components.end(); it++)
		{
			std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(*it);
			if (rtn)
			{
				return rtn;
			}
			if (!rtn)
			{
				throw rend::Exception("COMPONENT TYPE COULD NOT BE FOUND");
			}
		}
	}
};



#endif