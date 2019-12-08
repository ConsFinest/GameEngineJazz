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
	shader = eng->context->createShader();
	shader->parse(source);
	return shader;
}

std::sr1::shared_ptr<rend::Shader> Skybox::createShaderFF(const std::string _loc)
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

std::sr1::shared_ptr<rend::Mesh> Skybox::createMesh(const std::string _loc, bool _conversion)
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

		mesh->parse(obj, _conversion);
	}
	return mesh;
}

std::sr1::shared_ptr<rend::Texture> Skybox::createTexture(const std::string _loc)
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

std::shared_ptr<Camera> Skybox::setCamera(std::shared_ptr<Camera> _cam)
{
	camera = _cam;
	return camera;
}

void Skybox::SkyBoxInit(const std::string & source, const std::string _mesh, const std::string _text)
{
	std::sr1::shared_ptr<Engine> eng = getEngine();
	cube = eng->getContext()->createTexture();
	cube->SetCubeMap();
	texture = createTexture(_text);
	shader = createShaderFF(source);
	mesh = createMesh(_mesh, true);
	conversion = createShaderFF("../shaders/HDRshader.txt");
	glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
	glm::mat4 captureViews[] =
	{
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	};

	conversion->setSampler("equirectangularMap", 0);
	conversion->setUniform("projection", captureProjection);
	
	for (unsigned int i = 0; i < 6; ++i)
	{
		conversion->setUniform("view", captureViews[i]);
		conversion->setMesh(mesh);
		conversion->render(camera->getRendText(),true,i+1);
	}


}

void Skybox::onDisplay()
{

}
