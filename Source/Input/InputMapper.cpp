#include "InputMapper.h"
#include "InputConstants.h"
#include "MappedInput.h"

#include "../Systems/SetupUtils.h"

#include <iostream>

#include <SDL.h>

namespace
{
	void AddRawMouseInput(std::vector<MappedInput>& mappedInput)
	{
		MappedInput mouseInput;
		mouseInput.m_rawInput = INPUT_MOUSE_MOTION;

		int x;
		int y;
		SDL_GetRelativeMouseState(&x, &y);

		mouseInput.m_rangeInputValue.x = x;
		mouseInput.m_rangeInputValue.y = y;

		mappedInput.push_back(mouseInput);
	}
}

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
	std::vector<MappedInput> mappedInput;

	GetRawInput(mappedInput);
	MapRawInput(mappedInput);
	ProcessMappedInput(mappedInput);
}

void InputMapper::GetRawInput(std::vector<MappedInput>& mappedInput)
{
	AddRawMouseInput(mappedInput);

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	/*if (keystate[SDL_SCANCODE_W])
	{
		mappedInput.m_rawInput = INPUT_W_PRESS;
	}*/

	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		MappedInput keyInput;

		switch (sdlEvent.type)
		{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				switch (sdlEvent.key.keysym.sym)
				{
					case SDLK_w:
						keyInput.m_rawInput = sdlEvent.type == SDL_KEYDOWN ? INPUT_W_PRESS : INPUT_W_RELEASE;
						break;

					case SDLK_a:
						keyInput.m_rawInput = sdlEvent.type == SDL_KEYDOWN ? INPUT_A_PRESS : INPUT_A_RELEASE;
						break;

					default:
						break;
				}
				break;
		}

		mappedInput.push_back(keyInput);
	}
}

void InputMapper::MapRawInput(std::vector<MappedInput>& mappedInput)
{
	// Go through the contexts and handle each mapped input

	// A double loop is unfortunate
	for (int i = 0; i < mappedInput.size(); ++i)
	{
		for (int j = 0; j < m_inputContexts.size(); ++j)
		{
			if (m_inputContexts[j].MapInput(mappedInput[i]))
			{
				break;
			}
		}
	}
}

void InputMapper::ProcessMappedInput(std::vector<MappedInput>& mappedInput)
{
	// Fire input callbacks here

	for (int i = 0; i < mappedInput.size(); ++i)
	{
		for (int j = 0; j < m_inputCallbacks.size(); ++j)
		{
			m_inputCallbacks[i](mappedInput[i]);
		}
	}
}

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