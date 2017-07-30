#ifndef APPLICATION_SHARDLITE
#define APPLICATION_SHARDLITE

#include "../Systems/SDLHandler.h"
#include "../Systems/RenderSystem.h"

#include "../Rendering/MeshManagement/MeshAssetManager.h"
#include "../Rendering/MeshManagement/MeshComponentManager.h"

#include "../Rendering/AssetLoading/TextureManager.h"
#include "../Rendering/Shaders/ShaderCache.h"

#include "../Scenes/GameSpecificScenes/TestScene.h"

class Application
{
public:
	void StartUpSystems();
	void ShutDownSystems();

	bool Update();

	SDL_Window* GetWindow() { return m_sdlHandler.GetWindow(); }

	static void Quit();

private:
	SDLHandler m_sdlHandler;
	RenderSystem m_renderSystem;
	MeshAssetManager meshAssetManager;
	MeshComponentManager m_meshComponentManager;

	ShaderCache m_shaderCache;
	TextureManager m_textureManager;

	TestScene m_testScene;

private:
	static bool m_quitFlag;

	double m_last = 0.f;
	double m_current = 0.f;
	double m_deltaTime = 0.f;
};

#endif