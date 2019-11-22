#include "renderer.h"



#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

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

void Renderer::rendererInit(const std::string & source, const std::string _mesh, const std::string _text)
{
	shader = createShaderFF(source);
	mesh = createMesh(_mesh);
	texture = createTexture(_text);
	mesh->setTexture("u_Texture", texture);
}

void Renderer::onDisplay()
{
	
		angle += 0.5;
		SDL_Event event = { 0 };

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				
			}
		}

		glClearColor(0.10f, 0.15f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		shader->setUniform("u_Projection", glm::perspective(glm::radians(65.0f), 1.0f, 0.1f, 100.0f));
		shader->setUniform("u_Model",
		glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(1, 0, 0))*
		glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0))*
		glm::translate(glm::mat4(1.0f), glm::vec3(5, -2, 45)));
		shader->setMesh(mesh);
		shader->render();

}
