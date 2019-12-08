#ifndef  _SKYBOX_H_
#define _SKYBOX_H_

#include "component.h"
#include <rend/rend.h>
#include "engine.h"

class Skybox : public Component
{
	GLuint programId;
	GLuint vaoId;
	std::sr1::shared_ptr<rend::Mesh> mesh;
	std::sr1::shared_ptr<rend::Mesh> meshSky;
	std::sr1::shared_ptr<rend::Texture> texture;
	std::sr1::shared_ptr<rend::Texture> cube;

	std::sr1::shared_ptr<rend::Shader> conversion;
	std::sr1::shared_ptr<rend::Shader> shader;
	std::sr1::shared_ptr<rend::Shader> background;


	std::shared_ptr<Camera> camera;

public:
	Skybox();
	~Skybox();
	void setTextToMesh();
	std::sr1::shared_ptr<rend::Shader> createShader(const std::string &source);
	std::sr1::shared_ptr<rend::Shader> createShaderFF(const std::string _loc);
	std::sr1::shared_ptr<rend::Mesh> createMesh(const std::string _loc, bool _conversion);
	std::sr1::shared_ptr<rend::Texture> createTexture(const std::string _loc);

	std::shared_ptr<Camera> setCamera(std::shared_ptr<Camera> _cam);

	void SkyBoxInit(const std::string &source, const std::string _mesh, const std::string _text);


	virtual void onDisplay();
};





#endif // ! _SKYBOX_H_
