#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "component.h"
#include <rend/rend.h>
#include "engine.h"

class Renderer: public Component
{
	GLuint programId;
	GLuint vaoId;
	std::sr1::shared_ptr<rend::Mesh> mesh;
	std::sr1::shared_ptr<rend::Texture> texture;
	std::sr1::shared_ptr<rend::Shader> shader;
	std::shared_ptr<Camera> camera;

public:
	Renderer();
	~Renderer();
	void setTextToMesh();
	int count = 0; 
	std::sr1::shared_ptr<rend::Shader> createShader(const std::string &source);
	std::sr1::shared_ptr<rend::Shader> createShaderFF(const std::string _loc);
	std::sr1::shared_ptr<rend::Mesh> createMesh(const std::string _loc);
	std::sr1::shared_ptr<rend::Texture> createTexture(const std::string _loc);
	
	std::shared_ptr<Camera> setCamera(std::shared_ptr<Camera> _cam);

	void rendererInit(const std::string &source, const std::string _mesh, const std::string _text);
	
	virtual void onDisplay();
};






#endif // !_TRIANGLERENDERER_H_
