#ifndef _INPUT_H_
#define _INPUT_H_
#include <vector>
#include "engine.h"


class Input
{

	//KEYBOARD
	std::weak_ptr<Input> self;
	std::vector<SDL_Keycode> keys;
	std::vector<SDL_Keycode> pressedKeys;
	std::vector<SDL_Keycode> releasedKeys;
	int MouseX;
	int MouseY;

    public:
	//input to be init once
	static std::shared_ptr<Input> init();
    void addKey(SDL_Keycode _key);
	void removeKey(SDL_Keycode _key);
	void setMousePos(int _x, int _y);
	glm::vec2 getMousePos();

	bool keyDown(SDL_Keycode _key);
	bool keyPressed(SDL_Keycode _key);
	bool keyUp(SDL_Keycode _key);

	void onTick();
		
};




#endif // !_INPUT_H_


//TODO MakeInitilaze for input manager 