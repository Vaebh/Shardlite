#ifndef RENDER_SYSTEM_SHARDLITE
#define RENDER_SYSTEM_SHARDLITE

#include "ISystem.h"

class RenderSystem : ISystem
{
public:
	//RenderSystem();

	int StartUp();
	int ShutDown();

	//void Draw();

private:
	// List of batches, maybe batches just take the form of meshes?
};

#endif