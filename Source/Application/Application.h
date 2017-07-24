#ifndef APPLICATION_SHARDLITE
#define APPLICATION_SHARDLITE

#include "../Systems/SDLHandler.h"
#include "../Systems/RenderSystem.h"

class Application
{
public:
	void StartUpSystems();
	void ShutDownSystems();

	SDL_Window* GetWindow() { return m_sdlHandler.GetWindow(); }

private:
	SDLHandler m_sdlHandler;
	RenderSystem m_renderSystem;
};

#endif