#ifndef  _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_

#include "component.h"
#include "engine.h"

class PlayerController : public Component
{
	std::shared_ptr<Entity> ent;
	std::shared_ptr<Entity> entCam;
	std::shared_ptr<Transform> trans;
	std::shared_ptr<Input> inp;
	std::shared_ptr<Camera> cam;
	glm::vec3 Right;
	glm::vec3 Front;
	glm::vec3 Up;
	bool camEnt;
	glm::vec3 offset;
	float prevY;

public:
	void onTick();
	void updateVectors();
	void pcInit();
	void pcInit(std::shared_ptr<Entity> _entcam, glm::vec3 _offset);
};


#endif // ! _PLAYER_CONTROLLER_H_
