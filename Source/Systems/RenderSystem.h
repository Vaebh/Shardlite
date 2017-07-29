#ifndef RENDER_SYSTEM_SHARDLITE
#define RENDER_SYSTEM_SHARDLITE

#include "ISystem.h"

class MeshComponentManager;

class RenderSystem : ISystem
{
public:
	void SetManagerReferences(MeshComponentManager* meshComponentManager);

	int StartUp();
	int ShutDown();

	void Draw();

private:
	// List of batches, maybe batches just take the form of meshes?

	MeshComponentManager* m_meshComponentManager;
};

#endif