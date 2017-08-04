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

	void AddRawKeyInput(std::vector<MappedInput>& mappedInput)
	{
		const Uint8* keystate = SDL_GetKeyboardState(NULL);

		// This is our accepted range
		for (int i = INPUT_SCANCODE_A; i <= INPUT_SCANCODE_UP; ++i)
		{
			if (keystate[i])
			{
				MappedInput keyInput;
				keyInput.m_rawInput = (RawInput)i;
				mappedInput.push_back(keyInput);
			}
		}

		/*if (keystate[SDL_SCANCODE_W])
		{
		mappedInput.m_rawInput = INPUT_W_PRESS;
		}

		mappedInput.push_back(keyInput);*/
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
	AddRawKeyInput(mappedInput);

	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				MappedInput mouseClickInput;
				if (sdlEvent.button.button == SDL_BUTTON_LEFT)
				{
					mouseClickInput.m_rawInput = INPUT_LEFT_CLICK_PRESS;
				}
				else if(sdlEvent.button.button == SDL_BUTTON_RIGHT)
				{
					mouseClickInput.m_rawInput = INPUT_RIGHT_CLICK_PRESS;
				}
				else if (sdlEvent.button.button == SDL_BUTTON_MIDDLE)
				{
					mouseClickInput.m_rawInput = INPUT_MIDDLE_CLICK_PRESS;
				}

				mappedInput.push_back(mouseClickInput);
				break;
		}
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
			m_inputCallbacks[j](mappedInput[i]);
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