#include "PBR.h"

PBR::PBR()
{
	programId = 0;
	vaoId = 0;
}

PBR::~PBR()
{
}

void PBR::setTextToMesh()
{
	mesh->setTexture("u_Texture", texture);
}

std::sr1::shared_ptr<rend::Shader> PBR::createShader(const std::string & source)
{
	std::sr1::shared_ptr<Engine> eng = getEngine();
	shader = eng->context->createShader();
	shader->parse(source);
	return shader;
}

std::sr1::shared_ptr<rend::Shader> PBR::createShaderFF(const std::string _loc)
{
	std::sr1::shared_ptr<Engine> eng = getEngine();
	shader = eng->context->createShader();
	{
		std::fstream f(_loc.c_str());

		if (!f.is_open())
		{
			std::cout << _loc << std::endl;
			throw rend::Exception("Failed to open shaderfile");
		}

		std::string obj;
		std::string line;

		while (!f.eof())
		{
			std::getline(f, line);
			obj += line + "\n";
		}

		shader->parse(obj);
	}
	return shader;

}

std::sr1::shared_ptr<rend::Mesh> PBR::createMesh(const std::string _loc, bool _conversion)
{
	std::sr1::shared_ptr<Engine> eng = getEngine();
	mesh = eng->context->createMesh();
	{
		std::ifstream f(_loc.c_str());
		if (!f.is_open())
		{
			std::cout << _loc << std::endl;
			throw rend::Exception("Failed to open model");
		}

		std::string obj;
		std::string line;

		while (!f.eof())
		{
			std::getline(f, line);
			obj += line + "\n";
		}

		mesh->parse(obj);
	}
	return mesh;
}

std::sr1::shared_ptr<rend::Texture> PBR::createTexture(const std::string _loc)
{

	std::sr1::shared_ptr<Engine> eng = getEngine();
	texture = eng->context->createTexture();
	{
		int w = 0;
		int h = 0;
		int bpp = 0;

		unsigned char *data = stbi_load(_loc.c_str(),
			&w, &h, &bpp, 3);
	
		if (!data)
		{
			throw rend::Exception("Failed to open texture");
		}

		texture->setSize(w, h);

		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				int r = y * w * 3 + x * 3;

				texture->setPixel(x, y, glm::vec3(
					data[r] / 255.0f,
					data[r + 1] / 255.0f,
					data[r + 2] / 255.0f));
			}
		}

		stbi_image_free(data);
	}
	return texture;
}

std::sr1::shared_ptr<rend::Texture> PBR::createTextureHDR(const std::string _loc)
{
	std::sr1::shared_ptr<Engine> eng = getEngine();
	texture = eng->context->createTexture();
	{
		int w = 0;
		int h = 0;
		int bpp = 0;

		float *data = stbi_loadf(_loc.c_str(),
			&w, &h, &bpp, 0);
		
		if (!data)
		{
			throw rend::Exception("Failed to open texture");
		}

		texture->setSize(w, h);

		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
					int r = y * w * 3 + x * 3;

					texture->setPixel(x, y, glm::vec3(
						data[r] / 255.0f,
						data[r + 1] / 255.0f,
						data[r + 2] / 255.0f));
				
			}
		}

		stbi_image_free(data);
	}
	return texture;
}

std::shared_ptr<Camera> PBR::setCamera(std::shared_ptr<Camera> _cam)
{
	camera = _cam;
	return camera;
}

void PBR::rendererInitPBR(const std::string & source, const std::string _mesh, const std::string _text, const std::string _alb, const std::string _norm, const std::string _met, const std::string _rough, const std::string _ao, const std::string _ir)
{
	shader = createShaderFF(source);
	mesh = createMesh(_mesh, false);
	texture = createTexture(_text);
	albedoMap = createTexture(_alb);
	normalMap = createTexture(_norm);
	metallicMap = createTexture(_met);
	roughnessMap = createTexture(_rough);
	aoMap = createTexture(_ao);
	irMap = createTexture(_ir);

	mesh->setTexture("u_Texture", texture);

	mesh->setTexture("u_AlbedoMap", albedoMap);
	mesh->setTexture("u_NormalMap", normalMap);
	mesh->setTexture("u_MetallicMap", metallicMap);
	mesh->setTexture("u_RoughnessMap", roughnessMap);
	mesh->setTexture("u_AoMap", albedoMap);
	mesh->setTexture("u_IrMap", irMap);
	shader->setMesh(mesh);
}

void PBR::onDisplay()
{
	std::sr1::shared_ptr<Entity> ent = getEntity();
	std::sr1::shared_ptr<Transform> transform = ent->getComponent<Transform>();
	//transform->addRot({ 0, 1, 0 });

	std::cout << transform->getPos().x << " " << transform->getPos().y << " " << transform->getPos().z << std::endl;

	//shader->setUniform("u_LightPos", glm::vec3(0, 0, 5));
	shader->setUniform("u_CamPos", getEngine()->currentCam.lock()->getPos());
	//shader->setUniform("u_LightColor", glm::vec3(300.0f, 300.0f, 300.0f));
	if (getEngine()->currentCam.lock()->getRendText() != NULL)
	{
		shader->setUniform("u_View", glm::inverse(getEngine()->currentCam.lock()->getView()));
		shader->setUniform("u_Projection", getEngine()->currentCam.lock()->getProj());
		shader->setUniform("u_Model", transform->getModel());
		shader->render(getEngine()->currentCam.lock()->getRendText(), false);
	}
	else
	{
		shader->setUniform("u_View", glm::inverse(getEngine()->currentCam.lock()->getView()));
		shader->setUniform("u_Projection", getEngine()->currentCam.lock()->getProj());
		shader->setUniform("u_Model", transform->getModel());
		shader->render();
	}

}
