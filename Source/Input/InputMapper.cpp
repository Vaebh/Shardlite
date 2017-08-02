#include "InputMapper.h"
#include "InputConstants.h"
#include "MappedInput.h"

#include "../Systems/SetupUtils.h"

#include <SDL.h>

int InputMapper::StartUp()
{
	SDL_SetRelativeMouseMode(SDL_TRUE);

	return SETUP_SUCCESS;
}

int InputMapper::ShutDown()
{
	return SETUP_SUCCESS;
}

void InputMapper::UpdateInput()
{
	MappedInput mappedInput;

	GetRawInput(mappedInput);
	MapRawInput(mappedInput);
	ProcessMappedInput(mappedInput);
}

void InputMapper::GetRawInput(MappedInput& mappedInput)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	/*if (keystate[SDL_SCANCODE_W])
	{
	mappedInput.m_rawInput = INPUT_W_PRESS;
	}*/

	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
			case SDL_MOUSEMOTION:
				mappedInput.m_rawInput = INPUT_MOUSE_MOTION;

				int x;
				int y;
				SDL_GetRelativeMouseState(&x, &y);
				mappedInput.m_rangeInputValue.x = x;
				mappedInput.m_rangeInputValue.y = y;
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
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
				break;
		}
	}
}

void InputMapper::MapRawInput(MappedInput& mappedInput)
{

}

void InputMapper::ProcessMappedInput(MappedInput& mappedInput)
{


void InputMapper::AddContext(InputContext& in_context)
{
	m_inputContexts.push_back(in_context);
}

void InputMapper::SubscribeToInput(InputCallback callback)
{
	m_inputCallbacks.push_back(callback);
}

//void InputMapper::MapRawInput(MappedInput& mappedInput)
//{
//	// Loop through input to form a possible mapped input
//	/*for (int i = 0; i < m_inputContexts.size(); ++i)
//	{
//		if (m_inputContexts[i].MapInput(mappedInput))
//		{
//			inputMapped = true;
//		}
//	}*/
//
//	/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
//
//
//	for (int i = 0; i < m_inputContexts.size(); ++i)
//	{
//		/*if (m_inputContexts[i].ProcessInput(mappedInput))
//		{
//			return;
//		}*/
//	}
//}

//void InputMapper::ProcessInput(MappedInput& mappedInput)
//{
//	for (int i = 0; i < m_inputContexts.size(); ++i)
//	{
//		if (m_inputContexts[i].ProcessInput(mappedInput))
//		{
//			return;
//		}
//	}
//}