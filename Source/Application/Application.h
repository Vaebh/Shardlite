#ifndef APPLICATION_SHARDLITE
#define APPLICATION_SHARDLITE

#include "../Systems/SDLHandler.h"

class Application
{
public:
	void StartUpSystems();
	void ShutDownSystems();

	SDL_Window* GetWindow() { return m_sdlHandler.GetWindow(); }

private:
	SDLHandler m_sdlHandler;
};

#endif