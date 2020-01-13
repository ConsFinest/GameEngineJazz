#include "skyBox.h"

Skybox::Skybox()
{
}

Skybox::~Skybox()
{
}

void Skybox::setTextToMesh()
{
	mesh->setTexture("u_Texture", texture);
}

std::sr1::shared_ptr<rend::Shader> Skybox::createShader(const std::string & source)
{
	std::sr1::shared_ptr<Engine> eng = getEngine();
	shader = eng->getContext()->createShader();
	shader->parse(source);
	return shader;
}

std::sr1::shared_ptr<rend::Shader> Skybox::createShaderFF(const std::string _loc)
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

std::sr1::shared_ptr<rend::Mesh> Skybox::createMesh(const std::string _loc, bool _conversion)
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

std::sr1::shared_ptr<rend::Texture> Skybox::createTexture(const std::string _loc)
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
	return texture;
}

std::shared_ptr<Camera> Skybox::setCamera(std::shared_ptr<Camera> _cam)
{
	camera = _cam;
	return camera;
}

void Skybox::SkyBoxInit(const std::string & source, const std::string _mesh, const std::string _text)
{

}

void Skybox::onDisplay()
{

}
