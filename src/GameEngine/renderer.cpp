#include "renderer.h"



#define WINDOW_WIDTH 1024		
#define WINDOW_HEIGHT 760

Renderer::Renderer()
{
	
}

Renderer::~Renderer()
{
	
}

void Renderer::setTextToMesh()
{
	mesh->setTexture("u_Texture", texture);
}

std::sr1::shared_ptr<rend::Shader> Renderer::createShader(const std::string & source)
{
	std::sr1::shared_ptr<Engine> eng = getEngine();
	shader = eng->context->createShader();
	shader->parse(source);
	return shader;
}

std::sr1::shared_ptr<rend::Shader> Renderer::createShaderFF(const std::string _loc)
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

std::sr1::shared_ptr<rend::Mesh> Renderer::createMesh(const std::string _loc)
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

std::sr1::shared_ptr<rend::Texture> Renderer::createTexture(const std::string _loc)
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

std::shared_ptr<Camera> Renderer::setCamera(std::shared_ptr<Camera> _cam)
{
	camera = _cam;
	return camera;
}

void Renderer::rendererInit(const std::string & source, const std::string _mesh, const std::string _text)
{
	shader = createShaderFF(source);
	mesh = createMesh(_mesh);
	texture = createTexture(_text);
	mesh->setTexture("u_Texture", texture);
	pbr = false;
}

void Renderer::rendererInitPBR(const std::string & source, const std::string _mesh, const std::string _text, const std::string _alb, const std::string _norm, const std::string _met, const std::string _rough, const std::string _ao)
{
	shader = createShaderFF(source);
	mesh = createMesh(_mesh);
	texture = createTexture(_text);
	albedoMap = createTexture(_alb);
	normalMap = createTexture(_norm);
	metallicMap = createTexture(_met);
	roughnessMap = createTexture(_rough);
	aoMap = createTexture(_ao);
	mesh->setTexture("u_Texture", texture);
	

	mesh->setTexture("u_AlbedoMap", albedoMap);
	mesh->setTexture("u_NormalMap", normalMap);
	mesh->setTexture("u_MetallicMap", metallicMap);
	mesh->setTexture("u_RoughnessMap", roughnessMap);
	mesh->setTexture("u_AoMap", albedoMap);

	//albedo = glm::vec3(0.5, 0.5,0.5);
	//metallic = 1;
	//roughness = 1.0f;
	//ao = 1.0f;
	pbr = true;
}

void Renderer::onDisplay()
{

		std::sr1::shared_ptr<Entity> ent = getEntity();
		std::sr1::shared_ptr<Transform> transform = ent->getComponent<Transform>();

		std::cout << transform->getPos().x << " " << transform->getPos().y << " " << transform->getPos().z << std::endl;
		shader->setUniform("u_LightPos", glm::vec3(0, 0, 5));
		if (pbr == false)
		{
			shader->setUniform("u_Emissive", glm::vec3(0, 0, 0));
			shader->setUniform("u_Ambient", glm::vec3(0.0, 0.0, 0.0));
		}
		if (pbr == true)
		{
			//shader->setUniform("u_Roughness", roughness);
			shader->setUniform("u_CamPos", getEngine()->currentCam.lock()->getPos());
			shader->setUniform("u_LightColor", glm::vec3(300.0f, 300.0f, 300.0f));

			//shader->setUniform("u_Ao", ao);
			//shader->setUniform("u_Metallic", metallic);
			//shader->setUniform("u_Albedo", albedo);
		}
		//transform->addTrans(glm::vec3(0, 50, 0));

		shader->setUniform("u_View", glm::inverse(getEngine()->currentCam.lock()->getView()));
		shader->setUniform("u_Projection", getEngine()->currentCam.lock()->getProj());
		//shader->setUniform("u_Projection", camera->getProj());
		//shader->setUniform("u_View", camera->getView());
		shader->setUniform("u_Model", transform->getModel());
		shader->setMesh(mesh);
		if (getEngine()->currentCam.lock()->getRendText() != NULL)
		{
			shader->render(getEngine()->currentCam.lock()->getRendText());
		}
		else
		{
			shader->render();
		}
	

}
