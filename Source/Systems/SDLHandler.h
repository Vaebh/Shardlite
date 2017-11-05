#ifndef SDL_HANDLER_SHARDLITE
#define SDL_HANDLER_SHARDLITE

#include "../Systems/ISystem.h"

class SDL_Window;

class SDLHandler : ISystem
{
public:
	SDLHandler() {}
	~SDLHandler() {}

	int StartUp();
	int ShutDown();

	SDL_Window* GetWindow() { return m_gameWindow; }

private:
	SDL_Window* m_gameWindow;
};

#endif