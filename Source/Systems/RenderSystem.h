#ifndef RENDER_SYSTEM_SHARDLITE
#define RENDER_SYSTEM_SHARDLITE

#include "ISystem.h"
#include "../Rendering/DrawCallObject.h"
#include <vector>

class MeshComponentManager;
class SDL_Window;

class RenderSystem : ISystem
{
public:
	RenderSystem() {}
	~RenderSystem() {}

	RenderSystem(const RenderSystem&) =delete;
	RenderSystem& operator=(const RenderSystem&) =delete;

	void SetManagerReferences(MeshComponentManager* meshComponentManager, SDL_Window* gameWindow);

	int StartUp();
	int ShutDown();

	void ProcessMeshesForRendering();

	void Draw();

private:
	MeshComponentManager* m_meshComponentManager;
	SDL_Window* m_gameWindow;

	std::vector<DrawCallObject> m_drawCallObjs;
};

#endif