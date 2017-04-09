#include "TextureManager.h"
#include "Texture.h"

#include <iostream>

namespace
{
	const int DefaultCacheSize = 5;
}

TextureManager::TextureManager()
{
	//_textureMap = std::map<const GLchar*, unsigned char*>();
}

TextureManager::~TextureManager()
{

}

Texture* TextureManager::RequestTexture(const GLchar* in_texName)
{
	if (_textureMap.find(in_texName) == _textureMap.end())
	{
		unsigned char* imageData = LoadTextureFromFile(in_texName);
		if (imageData == nullptr)
		{
			return nullptr;
		}

		Texture* tex = new Texture(imageData);

		_textureMap[in_texName] = tex;
	}

	return _textureMap[in_texName];
}

unsigned char* TextureManager::LoadTextureFromFile(const GLchar* in_texName)
{
	GLuint* texture = new GLuint;
	glGenTextures(1, texture);
	GLint width = 0, height = 0;

	unsigned char* image = nullptr;

	std::string amendedPath(in_texName);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);
	image = SOIL_load_image(amendedPath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (image == NULL)
	{
		std::cout << "Image " << in_texName << " is null!" << std::endl;
		std::cout << "SOIL error: " << SOIL_last_result() << std::endl;

		return NULL;
	}

	return image;
}