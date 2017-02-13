#ifndef MESH_MANAGER_SHARDLITE
#define MESH_MANAGER_SHARDLITE

class Mesh;

class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	Mesh* LoadMesh(const char* meshName);
	Mesh* GetMesh(const char* meshName);
};

#endif