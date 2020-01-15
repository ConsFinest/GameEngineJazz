#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "component.h"
#include "engine.h"


class Physics : public Component
{
	bool kinematic;
	bool first;
	float gravity;
	glm::vec3 vel;

public:
	Physics();
	void onTick();
	void setVelocity(glm::vec3 _vel);
	void addVelocity(glm::vec3 _vel);

	void setKinematic(bool _set);
	bool getKinematic();
	glm::vec3 getVelocity();
	void setGravity(float _value);
	void reduceGravity(float _value);
};


#endif // !_PHYSICS_H_
