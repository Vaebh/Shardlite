#include "InputMapper.h"

#include <SDL.h>

void InputMapper::DetectInput()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
}