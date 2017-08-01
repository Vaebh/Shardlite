#include "InputMapper.h"
#include "InputConstants.h"

#include <SDL.h>

struct MappedInput
{
	RawInput m_rawInput;
	Input m_processedInput;
};

void InputMapper::MapInput()
{
	RawInput newRawInput;
	Input mappedInput;

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_W])
	{
		newRawInput = INPUT_W_PRESS;
	}

	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
		switch (sdlEvent.key.keysym.sym)
		{
			case SDLK_w:
				printf("W key press detected\n");
				break;

				/*case SDL_KEYUP:
					printf("Key release detected\n");
					break;*/

			default:
				break;
		}
	}
}