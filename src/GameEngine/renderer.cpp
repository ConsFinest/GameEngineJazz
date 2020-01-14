#include "renderer.h"



#define WINDOW_WIDTH 1024		
#define WINDOW_HEIGHT 760

Renderer::Renderer()
{
	programId = 0;
	vaoId = 0;
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
	shader = eng->getContext()->createShader();
	shader->parse(source);
	return shader;
}

std::sr1::shared_ptr<rend::Shader> Renderer::createShaderFF(const std::string _loc)
{
	std::sr1::shared_ptr<Engine> eng = getEngine();
	shader = eng->getContext()->createShader();
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
	mesh = eng->getContext()->createMesh();
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
	texture = eng->getContext()->createTexture();
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
	//texture->getId();
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
	shader->setMesh(mesh);
	std::cout << "renderer init" << std::endl;

}

void Renderer::onDisplay()
{

		std::sr1::shared_ptr<Entity> ent = getEntity();
		std::sr1::shared_ptr<Transform> transform = ent->getComponent<Transform>();
		glEnable(GL_DEPTH_TEST);

		//std::cout << transform->getPos().x << " " << transform->getPos().y << " " << transform->getPos().z << std::endl;
	
		shader->setUniform("u_LightPos", glm::vec3(0, 0, 5));
		
		shader->setUniform("u_Emissive", glm::vec3(0.2, 0.2, 0.2));
		shader->setUniform("u_Ambient", glm::vec3(0.0, 0.0, 0.0));
		
		if (getEngine()->currentCam.lock()->getRendText() != NULL)
		{
			
		}
		else
		{
			shader->setUniform("u_View", glm::inverse(getEngine()->currentCam.lock()->getView()));
			shader->setUniform("u_Projection", getEngine()->currentCam.lock()->getProj());
			shader->setUniform("u_Model", transform->getModel());
			shader->render();
		}
	

}
