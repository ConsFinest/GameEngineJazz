#ifndef _TRIANGLERENDERER_H_
#define _TRIANGLERENDERER_H_

#include "component.h"
#include <rend/rend.h>

class Triangle: public Component
{
	GLuint programId;
	GLuint vaoId;

public:
	Triangle();
	~Triangle();
	

	virtual void onDisplay();
};






#endif // !_TRIANGLERENDERER_H_
