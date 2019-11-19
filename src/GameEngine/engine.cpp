#include "engine.h"
#include "entity.h"


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

Engine::~Engine()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

std::shared_ptr<Engine> Engine::intialize()
{
	std::shared_ptr<Engine>eng = std::make_shared<Engine>();
	eng->self = eng;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw rend::Exception("SDL FAILED TO INITIALISE");
	}

	eng->window = SDL_CreateWindow("Lab 4 - Architecture",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(eng->window))
	{
		throw rend::Exception("OPENGL CONTEXT FAILED TO INITIALISE");
	}

	eng->context = rend::Context::initialize();

	return eng;
}

std::shared_ptr<Entity> Engine::addEntity()
{
	std::shared_ptr<Entity>ent = std::make_shared<Entity>();
	entities.push_back(ent);
	ent->engine = self;
	ent->self = ent;
	return ent;
}

void Engine::start()
{
	running = true;
	while (running)
	{
		SDL_Event event = { 0 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}
		
		for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
		{
			(*it)->tick();
			std::cout << "Entity updated" << std::endl;
		}
		for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
		{
			(*it)->display();
			std::cout << "Entity Drawns" << std::endl;
		}
		SDL_GL_SwapWindow(window);
	}

}

void Engine::stop()
{
	running = false;
}

std::sr1::shared_ptr<rend::Context> Engine::getContext()
{
	return std::sr1::shared_ptr<rend::Context>();
}

std::sr1::shared_ptr<rend::Shader> Engine::createShader(const std::string & source)
{
	std::sr1::shared_ptr<rend::Shader> shader = context->createShader();
	shader->parse(source);
	return shader;
}

std::sr1::shared_ptr<rend::Mesh> Engine::createMesh(const std::string _loc)
{
	std::sr1::shared_ptr<rend::Mesh> shape = context->createMesh();
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

		shape->parse(obj);
	}
	return shape;

}

std::sr1::shared_ptr<rend::Texture> Engine::createTexture(const std::string _loc)
{
	std::sr1::shared_ptr<rend::Texture> texture = context->createTexture();
	{
		int w = 0;
		int h = 0;
		int bpp = 0;

		unsigned char *data = stbi_load(_loc.c_str(),
			&w, &h, &bpp, 3);

		if (!data)
		{
			throw rend::Exception("Failed to open image");
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


