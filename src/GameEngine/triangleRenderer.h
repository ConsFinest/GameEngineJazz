#ifndef _TRIANGLERENDERER_H_
#define _TRIANGLERENDERER_H_

#include "component.h"
#include "Exception.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <exception>



class Triangle: public Component
{
	SDL_Window *window;
	GLuint programId;
	GLuint vaoId;

public:
	Triangle();
	~Triangle();
	

	virtual void onDisplay();
};






#endif // !_TRIANGLERENDERER_H_
