#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "component.h"
#include "engine.h"
#include "input.h"

class Input;

class Camera : public Component
{
	glm::vec3 camPos;
	glm::mat4 viewMat;
	glm::mat4 projMat;
	float angle;
	std::sr1::shared_ptr<rend::RenderTexture> renderText;
	bool playerControlled;
	glm::vec3 Right;
	glm::vec3 Front;
	glm::vec3 Up;
	bool windowLock;
	bool currentCam;
	glm::vec3 offset;


public:

	void setNotCurrent();
	void setCurrent();
	bool getCurrent();
	glm::vec3 getPos();
	glm::mat4 getView();
	glm::mat4 getProj();
	void setRendText();
	void cameraInit(float _angle);
	std::sr1::shared_ptr<rend::RenderTexture> getRendText();
	virtual void onTick();
	void playerControll(bool _value);

};





#endif // !_CAMERA_H_
