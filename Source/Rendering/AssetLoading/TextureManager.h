#ifndef SHARDLITE_TEXTURE_MANAGER
#define SHARDLITE_TEXTURE_MANAGER

#ifdef _WIN32
#include <glew.h>
#include <gl\GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

#include <map>

class Texture;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	Texture* RequestTexture(const GLchar* in_texName);

	unsigned char* LoadTextureFromFile(const GLchar* in_texName);

private:
	std::map<const GLchar*, Texture*> _textureMap;
};

#endif