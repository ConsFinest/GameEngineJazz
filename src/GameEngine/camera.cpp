#include "camera.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 760

void Camera::setNotCurrent()
{
	currentCam = false;
}

void Camera::setCurrent()
{
	//TODO revise this function so everything isn't always false
	currentCam = true;
	std::vector<std::sr1::weak_ptr<Camera>> cameras;
	cameras = getEngine()->cameras;
	for (auto it = cameras.begin(); it != cameras.end(); it++)
	{
		std::shared_ptr<Camera> cam = (*it).lock();
		if (cam->getEntity() != getEntity())
		{
			cam->setNotCurrent();
		}
	}
}

bool Camera::getCurrent()
{
	return currentCam;
}

glm::vec3 Camera::getPos()
{
	std::sr1::shared_ptr<Entity> ent = getEntity();
	std::sr1::shared_ptr<Transform> transform = ent->getComponent<Transform>();
	return transform->getPos();
}

//ToDo - destruction remove camera from list inside engine

glm::mat4 Camera::getView()
{

	std::sr1::shared_ptr<Entity> ent = getEntity();
	std::sr1::shared_ptr<Transform> transform = ent->getComponent<Transform>();
	
	return transform->getModel();
}

glm::mat4 Camera::getProj()
{
	projMat = glm::perspective(glm::radians(angle), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.0f);
	return projMat;
}

void Camera::setRendText()
{
	std::sr1::shared_ptr<Engine> eng = getEngine();
	renderText = eng->getContext()->createRenderTexture();
}

void Camera::cameraInit(float _angle)
{
	windowLock = true;
	angle = _angle;
	camPos = glm::vec3(0, 0, 0);
	std::sr1::shared_ptr<Entity> ent = getEntity();
	std::sr1::shared_ptr<Transform> transform = ent->getComponent<Transform>();
	camPos = transform->getPos();
	std::sr1::shared_ptr<Engine> eng = getEngine();
	eng->cameras.push_back(ent->getComponent<Camera>());

	glm::mat4 t(1.0f);
	t = glm::translate(t, glm::vec3(0, 1, 0));
	Up = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	Up = glm::normalize(Up);
	updateCamVectors();


}

std::sr1::shared_ptr<rend::RenderTexture> Camera::getRendText()
{
	return renderText;
}

void Camera::onTick()
{
	std::shared_ptr<Engine> eng = getEngine();
	
	float movementSpeed = 10.0f;
	float rotationSpeed = 20.0f;
	float deltaTime = getEngine()->getDeltaTime();
	movementSpeed = movementSpeed * deltaTime;
	rotationSpeed = rotationSpeed * deltaTime;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (playerControlled &&eng->checkIfCurrent())
	{
		
		std::sr1::shared_ptr<Entity> ent = getEntity();
		std::sr1::shared_ptr<Transform> transform = ent->getComponent<Transform>();
		glm::vec3 pos = transform->getPos();
		glm::vec3 rot = transform->getRot();
		std::shared_ptr<Input> inp = getEngine()->getInput();
		
		if (inp->keyDown(SDL_SCANCODE_L))
		{
			if (windowLock)
			{
				SDL_ShowCursor(1);
				SDL_SetWindowGrab(eng->getWindow(), SDL_FALSE);
				windowLock = false;
			}
			if (!windowLock)
			{
				SDL_ShowCursor(0);
				SDL_SetWindowGrab(eng->getWindow(), SDL_TRUE);
				SDL_WarpMouseInWindow(eng->getWindow(), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
				windowLock = true;
			}
		}
		if (inp->keyDown(SDL_SCANCODE_W))
		{
			std::cout << "moving forward" << std::endl;
			pos += Front * movementSpeed;
		}
		if (inp->keyDown(SDL_SCANCODE_S))
		{
			std::cout << "moving backwards" << std::endl;
			pos -= Front * movementSpeed;
		}
		if (inp->keyDown(SDL_SCANCODE_A))
		{
			std::cout << "moving left" << std::endl;
			pos -= Right * movementSpeed;
		}
		if (inp->keyDown(SDL_SCANCODE_D))
		{
			std::cout << "moving right" << std::endl;
			pos += Right * movementSpeed;
		}
		updateCamVectors();
		transform->addRot({-(inp->getMousePos().x * rotationSpeed), -(inp->getMousePos().y * rotationSpeed), 0 });
		transform->setPos(pos);
		//TODO make camera angles be seperate
	}
	
}

void Camera::playerControll(bool _value)
{
	playerControlled = _value;
}

void Camera::updateCamVectors()
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


