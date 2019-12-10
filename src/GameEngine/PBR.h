#ifndef  _PBR_H_
#define _PBR_H_

#include "component.h"
#include <rend/rend.h>
#include "engine.h"

class PBR : public Component
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
	std::sr1::shared_ptr<rend::Texture> irMap;

	std::sr1::shared_ptr<rend::Shader> shader;
	std::sr1::shared_ptr<rend::Shader> conversion;
	std::sr1::shared_ptr<rend::Shader> skyBox;

	std::shared_ptr<Camera> camera;

public: 

	PBR();
	~PBR();
	void setTextToMesh();
	std::sr1::shared_ptr<rend::Shader> createShader(const std::string &source);
	std::sr1::shared_ptr<rend::Shader> createShaderFF(const std::string _loc);
	std::sr1::shared_ptr<rend::Mesh> createMesh(const std::string _loc, bool _conversion);
	std::sr1::shared_ptr<rend::Texture> createTexture(const std::string _loc);
	std::sr1::shared_ptr<rend::Texture> createTextureHDR(const std::string _loc);

	std::shared_ptr<Camera> setCamera(std::shared_ptr<Camera> _cam);

	void rendererInitPBR(const std::string & source, const std::string _mesh, const std::string _text, const std::string _alb, const std::string _norm, const std::string _met, const std::string _rough, const std::string _ao, const std::string _ir);

	float angle = 0;

	virtual void onDisplay();

};







#endif // ! _PBR_H_
