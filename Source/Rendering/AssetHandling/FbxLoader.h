#ifndef FBX_LOADER_SHARDLITE
#define FBX_LOADER_SHARDLITE

#include <vector>
#include <glew.h>
#include <gl\GL.h>

class Mesh;

class FbxLoader
{
public:
	static Mesh* LoadFbx(const char* fileName);

private:
	FbxLoader();
};

#endif