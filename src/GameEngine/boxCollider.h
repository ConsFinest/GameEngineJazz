#ifndef _BOX_COLLIDER_H_
#define _BOX_COLLIDER_H_

#include "component.h"

class Engine;
class Entity;
class Transform;

class boxCollider : public Component
{
	void onTick();
	glm::vec3 size;
	glm::vec3 offset;
	glm::vec3 position;



	bool isColliding(glm::vec3 _pos, glm::vec3 _size);
	glm::vec3 collisionResponse(glm::vec3 _pos, glm::vec3 _size);

public:

	void onInit();

	void setSize(glm::vec3 size);
	void setOffset(glm::vec3 _offset);

	

};





#endif // 
