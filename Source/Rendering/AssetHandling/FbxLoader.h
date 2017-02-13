#ifndef FBX_LOADER_SHARDLITE
#define FBX_LOADER_SHARDLITE

#include <vector>
#include <glew.h>
#include <gl\GL.h>

class FbxLoader
{
public:
	static std::vector<GLfloat> LoadFbx(const char* fileName);

private:
	FbxLoader();
};

#endif