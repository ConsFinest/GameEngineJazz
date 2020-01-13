#ifndef  _GUI_H_
#define _GUI_H_

#include <memory>
#include <rend/rend.h>
#include "component.h"
#include "engine.h"

class Mesh;
class Shader;

class GUI : public Component
{
	std::shared_ptr<rend::Mesh> mesh;
	std::shared_ptr<rend::Shader> shader;
	std::shared_ptr<rend::Buffer> Posbuffer;
	std::shared_ptr<rend::Buffer> TCbuffer;
	std::shared_ptr<rend::Texture> texture;
	
	std::shared_ptr<rend::Shader> createShader(const std::string _loc);
	std::shared_ptr<rend::Mesh> createMesh();
	std::shared_ptr<rend::Buffer> createBuffer();
	std::shared_ptr<rend::Texture> createTexture(const std::string _loc);

	GLuint programId;

	glm::vec4 color;
	glm::vec3 GUIscale;
	glm::vec2 pos;
	glm::mat4 projection;

public: 
	GUI();
	void GUIInit(const std::string &source, glm::vec3 _scale, const std::string & _text, glm::vec2 _pos);
	virtual void onDisplay();
	void setPos(glm::vec2 _pos);

};




#endif // ! _GUI_H_
