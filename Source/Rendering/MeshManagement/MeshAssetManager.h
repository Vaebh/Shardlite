#ifndef MESH_MANAGER_SHARDLITE
#define MESH_MANAGER_SHARDLITE
// This class is two things:
// A) A format independant interface from which to load and unload mesh data from files
// B) A container for all of the actual mesh object data

#include "Mesh.h"
#include "../System/Batch.h"

#include <map>

class MeshAssetManager
{
public:
	MeshAssetManager();
	~MeshAssetManager();

	static Mesh* LoadMesh(const char* meshName);
	static Mesh* GetMesh(const char* meshName);

	static std::map<int, Mesh*> GetMeshes();

private:
	static MeshAssetManager* Instance;

	std::map<int, Mesh*> m_meshes;
};

#endif