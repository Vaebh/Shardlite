#include "SDLHandler.h"
#include "../Systems/SetupUtils.h"

#include <SDL.h>
#include <iostream>

int SDLHandler::StartUp()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	m_gameWindow = SDL_CreateWindow("Shardlite", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_GRABBED);
	if (m_gameWindow == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

#ifdef __APPLE__
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

	SDL_GLContext gi_glcontext = SDL_GL_CreateContext(m_gameWindow);

	return SETUP_SUCCESS;
}

int SDLHandler::ShutDown()
{
	SDL_DestroyWindow(m_gameWindow);
	SDL_Quit();

	return SETUP_SUCCESS;
}