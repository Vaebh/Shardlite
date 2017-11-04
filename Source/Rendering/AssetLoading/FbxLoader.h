#ifndef FBX_LOADER_SHARDLITE
#define FBX_LOADER_SHARDLITE

#include <vector>

#ifdef __WINDOWS__
#include <glew.h>
#include <gl\GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

class Mesh;

class FbxLoader
{
public:
	static Mesh* LoadFbx(std::string assetLocation, const char* assetName);

private:
	FbxLoader();
	~FbxLoader() {}

	FbxLoader(const FbxLoader&) =delete;
	FbxLoader& operator=(const FbxLoader&) =delete;
};

#endif
