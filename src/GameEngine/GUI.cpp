#include "GUI.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 760

std::shared_ptr<rend::Shader> GUI::createShader(const std::string _loc)
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

std::shared_ptr<rend::Mesh> GUI::createMesh()
{
	std::sr1::shared_ptr<Engine> eng = getEngine();
	mesh = eng->getContext()->createMesh();
	return mesh;
}

std::shared_ptr<rend::Buffer> GUI::createBuffer()
{
	std::sr1::shared_ptr<Engine> eng = getEngine();
	Posbuffer = eng->getContext()->createBuffer();

	return Posbuffer;
}

std::shared_ptr<rend::Texture> GUI::createTexture(const std::string _loc)
{
	std::sr1::shared_ptr<Engine> eng = getEngine();
	texture = eng->getContext()->createTexture();
	{
		int w = 0;
		int h = 0;
		int bpp = 0;

		unsigned char *data = stbi_load(_loc.c_str(),
			&w, &h, &bpp, 4);

		if (!data)
		{
			throw rend::Exception("Failed to open texture");
		}

		texture->setSize(w, h);

		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				int r = y * w * 4 + x * 4;

				texture->setPixel(x, y, glm::vec4(
					data[r] / 255.0f,
					data[r + 1] / 255.0f,
					data[r + 2] / 255.0f,
					data[r+3]/255.0f));
					
			}
		}

		stbi_image_free(data);
	}
	//texture->getId();
	return texture;
}

GUI::GUI()
{
	programId = 0;
}

void GUI::GUIInit(const std::string & source, glm::vec3 _scale, const std::string & _text, glm::vec2 _pos)
{
	pos = _pos;
	GUIscale = _scale;
	shader = createShader(source);
	mesh = createMesh();
	texture = createTexture(_text);
	//1 x 1 scale for size
	Posbuffer = createBuffer();
	{
		Posbuffer->add({ 0, 0 });
		Posbuffer->add({ 0, 1 });
		Posbuffer->add({ 1, 1 });
		Posbuffer->add({ 1, 1 });
		Posbuffer->add({ 1, 0 });
		Posbuffer->add({ 0, 0 });
		mesh->setBuffer("a_Position", Posbuffer);
	}
	//1 x 1 texture coords
	TCbuffer = createBuffer();
	{
		TCbuffer->add({ 0.0f,1.0f });
		TCbuffer->add({ 0.0f,0.0f });
		TCbuffer->add({ 1.0f,0.0f });
		TCbuffer->add({ 1.0f,0.0f });
		TCbuffer->add({ 1.0f,1.0f });
		TCbuffer->add({ 0.0f,1.0f });
		mesh->setBuffer("a_TexCoords", TCbuffer);
	}
	mesh->setTexture("u_Texture", texture);
	std::cout << "GUIrender init" << std::endl;
}

void GUI::onDisplay()
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, { pos.x, pos.y, 0 });
    model = glm::scale(model, { GUIscale.x, GUIscale.y, 1.0f });
	shader->setUniform("u_Model", model);
	shader->setUniform("u_Projection", glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f));

	shader->setMesh(mesh);
    shader->render();
}

void GUI::setPos(glm::vec2 _pos)
{
	pos = _pos;
}
