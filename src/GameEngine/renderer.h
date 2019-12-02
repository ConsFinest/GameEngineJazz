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
	std::sr1::shared_ptr<rend::Texture> albedoMap;
	std::sr1::shared_ptr<rend::Texture> normalMap;
	std::sr1::shared_ptr<rend::Texture> metallicMap;
	std::sr1::shared_ptr<rend::Texture> roughnessMap;
	std::sr1::shared_ptr<rend::Texture> aoMap;


	std::sr1::shared_ptr<rend::Shader> shader;
	std::shared_ptr<Camera> camera;
	bool pbr;
	//glm::vec3 albedo;
	//float metallic;
	//float roughness;
	//float ao; //Ambeient Occlusion

public:
	Renderer();
	~Renderer();
	void setTextToMesh();
	std::sr1::shared_ptr<rend::Shader> createShader(const std::string &source);
	std::sr1::shared_ptr<rend::Shader> createShaderFF(const std::string _loc);
	std::sr1::shared_ptr<rend::Mesh> createMesh(const std::string _loc);
	std::sr1::shared_ptr<rend::Texture> createTexture(const std::string _loc);
	std::shared_ptr<Camera> setCamera(std::shared_ptr<Camera> _cam);
	void rendererInit(const std::string &source, const std::string _mesh, const std::string _text);
	void rendererInitPBR(const std::string & source, const std::string _mesh, const std::string _text, const std::string _alb, const std::string _norm, const std::string _met, const std::string _rough, const std::string _ao);

	float angle = 0;
	

	virtual void onDisplay();
};






#endif // !_TRIANGLERENDERER_H_
