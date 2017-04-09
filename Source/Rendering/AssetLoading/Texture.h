#ifndef SHARDLITE_TEXTURE
#define SHARDLITE_TEXTURE

#ifdef _WIN32
#include <glew.h>
#include <gl\GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

#include <vector>

class Texture
{
public:
	Texture(unsigned char* imageData);

private:
	unsigned char* _imageData;
};

#endif