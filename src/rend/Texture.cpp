#include "Texture.h"
#include "Context.h"
#include "Exception.h"

namespace rend
{

Texture::~Texture()
{
  GLuint delId = id;
  glDeleteTextures(1, &delId);
  pollForError();
  delete dataA;
}

Texture::Texture()
{
	dataA = NULL;
	//data.resize(NULL);
}

GLuint Texture::getTexId()
{
  return getId();
}

void Texture::setCubeMap()
{
	cubeMap = true;
}



GLuint Texture::getId()
{
	if (dirty && !cubeMap)
	{
		glBindTexture(GL_TEXTURE_2D, id);
		pollForError();

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_FLOAT, &data.at(0));
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_FLOAT, dataA);
		delete dataA;
		dataA = NULL;

		pollForError();

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		pollForError();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		pollForError();

		glGenerateMipmap(GL_TEXTURE_2D);
		pollForError();

		glBindTexture(GL_TEXTURE_2D, 0);
		pollForError();

		dirty = false;
	}
	if (dirty && cubeMap)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, id);
		for (unsigned int i = 0; i < 6; i++)
		{
				//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_FLOAT, &data.at(i));
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_FLOAT, dataA);

		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		dirty = false;
	}
  return id;
}

ivec2 Texture::getSize() const
{
  return size;
}

int Texture::getWidth() const
{
  return size.x;
}

int Texture::getHeight() const
{
  return size.y;
}

void Texture::setSize(unsigned int width, unsigned int height)
{
  dirty = true;
  size = ivec2(width, height);
  //data.resize(width * height);
  dataA = new glm::vec4[width*height];
}

void Texture::setPixel(unsigned int x, unsigned int y, vec3 rgb)
{
  setPixel(x, y, vec4(rgb, 1));
  bpp = 3;
}

void Texture::setPixel(unsigned int x, unsigned int y, vec4 rgba)
{
  dirty = true;
  bpp = 4;
  //data.at(size.x * (size.y - 1 - y) + x) = rgba;
  dataA[size.x * (size.y - 1 - y) + x] = rgba;
}

vec4 Texture::getPixel(unsigned int x, unsigned int y) const
{
  //return data.at(size.x * y + x);
	return dataA[size.x * y + x];
}

}
