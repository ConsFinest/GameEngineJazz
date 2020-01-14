#include "input.h"

std::shared_ptr<Input> Input::init()
{
	std::shared_ptr<Input> inp = std::make_shared<Input>();
	inp->self = inp;

	return inp;
}

void Input::addKey(SDL_Keycode _key)
{
	for (auto it = keys.begin(); it != keys.end(); it++)
	{
		if (*it == _key)
		{
			//checking if the key exists in the list
			return;
		}
	}
	std::cout << "keyadded: " << _key << std::endl;
	pressedKeys.push_back(_key);
	keys.push_back(_key);
}

void Input::removeKey(SDL_Keycode _key)
{
	releasedKeys.push_back(_key);
	for (auto it = keys.begin(); it != keys.end();)
	{
		if (*it == _key)
		{
			std::cout << "keyremoved: " << _key << std::endl;
			it = keys.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void Input::setMousePos(int _x, int _y)
{
	MouseX = _x;
	MouseY = _y;
	std::cout << MouseX << " " << MouseY << std::endl;
}

glm::vec2 Input::getMousePos()
{
	return glm::vec2(MouseX,MouseY);
}

bool Input::keyDown(SDL_Keycode _key)
{
	for (auto it = keys.begin(); it != keys.end(); it++) //Changed to keys so keys can be held
	{
		if (*it == _key)
		{
			return true;
		}
	}
	return false;
}

bool Input::keyPressed(SDL_Keycode _key)
{
	for (auto it = pressedKeys.begin(); it != pressedKeys.end(); it++) 
	{
		if (*it == _key)
		{
			return true;
		}
	}
	return false;
}

bool Input::keyUp(SDL_Keycode _key)
{
	for (auto it = releasedKeys.begin(); it != releasedKeys.end(); it++)
	{
		if (*it == _key)
		{
			return true;
		}
	}
	return false;
}

void Input::onTick()
{
	
	pressedKeys.clear();
	releasedKeys.clear();
	MouseX = 0;
	MouseY = 0;
	
}
