#include "playerController.h"
#include "physics.h"
#include <cmath>

void PlayerController::onTick()
{
	glm::vec3 pos = trans->getPos();
	glm::vec3 rot = trans->getRot();
	

	SDL_SetRelativeMouseMode(SDL_TRUE);
	float movementSpeed = 10.0f;
	float rotationSpeed = 20.0f;
	float deltaTime = getEngine()->getDeltaTime();
	movementSpeed = movementSpeed * deltaTime;
	rotationSpeed = rotationSpeed * deltaTime;
	if (inp->keyDown(SDL_SCANCODE_W))
	{
		//std::cout << "moving forward" << std::endl;
		pos += Front * movementSpeed;

	}
	if (inp->keyDown(SDL_SCANCODE_S))
	{
		//std::cout << "moving backwards" << std::endl;
		pos -= Front * movementSpeed;

	}
	if (inp->keyDown(SDL_SCANCODE_A))
	{
		//std::cout << "moving left" << std::endl;
		pos -= Right * movementSpeed;

	}
	if (inp->keyDown(SDL_SCANCODE_D))
	{
		//std::cout << "moving right" << std::endl;
		pos += Right * movementSpeed;

	}
	if (inp->keyPressed(SDL_SCANCODE_SPACE))
	{
		if (ent->searchComponents<Physics>())
		{
			std::shared_ptr<Physics> entPhys = ent->getComponent<Physics>();
		
			entPhys->addVelocity({ 0,0.2,0 });
			
		}
	}
	
	bool update = true;
	if (ent->searchComponents<Camera>()) //stops cameras update if they aren't the active camera
	{
		cam = ent->getComponent<Camera>();
		if (!cam->getCurrent())
		{
			update = false;
		}
	}
	if (entCam->searchComponents<Camera>())
	{
		cam = entCam->getComponent<Camera>();
		if (!cam->getCurrent())
		{
			update = false;
		}
	}
	if (update)
	{
		
		updateVectors();
		//passing in camera in init
		if (camEnt && entCam->getComponent<Camera>()->getCurrent())
		{
			std::shared_ptr<Transform> transEnt = entCam->getComponent<Transform>();
			transEnt->setPos(pos);
			transEnt->addRot({ -(inp->getMousePos().x * rotationSpeed), -(inp->getMousePos().y * rotationSpeed), 0 });
			transEnt->setPos(pos -offset.z*Front + offset.y*Up +offset.x * Right);
			trans->addRot({ -(inp->getMousePos().x * rotationSpeed), 0, 0 });
			trans->setPos(pos);
		}
		if (!camEnt)
		{
			trans->addRot({ -(inp->getMousePos().x * rotationSpeed), -(inp->getMousePos().y * rotationSpeed), 0 });
			trans->setPos(pos);
		}
	}	
}

void PlayerController::updateVectors()
{
	std::sr1::shared_ptr<Entity> ent = getEntity();
	std::sr1::shared_ptr<Transform> transform = ent->getComponent<Transform>();
	glm::vec3 rot = transform->getRot();
	glm::mat4 t(1.0f);
	t = glm::rotate(t, glm::radians(rot.x), glm::vec3(0, 1, 0));
	t = glm::translate(t, glm::vec3(0, 0, -1));
	Front = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	Front = glm::normalize(Front);

	t = glm::mat4(1.0f);
	t = glm::rotate(t, glm::radians(rot.x), glm::vec3(0, 1, 0));
	t = glm::translate(t, glm::vec3(1, 0, 0));
	Right = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	Right = glm::normalize(Right);
}

void PlayerController::pcInit()
{
	wait = 0;
	camEnt = false;
	ent = getEntity();
	trans = ent->getComponent<Transform>();
	inp = getEngine()->getInput();
	glm::mat4 t(1.0f);
	t = glm::translate(t, glm::vec3(0, 1, 0));
	Up = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	Up = glm::normalize(Up);
	updateVectors();

}

void PlayerController::pcInit(std::shared_ptr<Entity> _entcam, glm::vec3 _offset)
{
	wait = 0;
	camEnt = true;
	offset = _offset;
	ent = getEntity();
	entCam = _entcam;
	trans = ent->getComponent<Transform>();
	inp = getEngine()->getInput();
	glm::mat4 t(1.0f);
	t = glm::translate(t, glm::vec3(0, 1, 0));
	Up = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	Up = glm::normalize(Up);
	updateVectors();
}
