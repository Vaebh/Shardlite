#include "HapticsSystem.h"

#include "SetupUtils.h"

#include <iostream>

#include <SDL.h>

int HapticsSystem::StartUp()
{
	return SETUP_SUCCESS;
}

int HapticsSystem::ShutDown()
{
	for (int i = 0; i < MAX_CONTROLLERS; ++i)
	{
		if (m_hapticHandles[i])
		{
			SDL_HapticClose(m_hapticHandles[i]);
		}
	}

	return SETUP_SUCCESS;
}

void HapticsSystem::SetHapticHandles(SDL_GameController* in_controllerHandles[MAX_CONTROLLERS], int numControllers)
{
	for (int i = 0; i < numControllers; ++i)
	{
		SDL_Joystick* joystickHandle = SDL_GameControllerGetJoystick(in_controllerHandles[i]);
		m_hapticHandles[i] = SDL_HapticOpenFromJoystick(joystickHandle);
	}
}

void HapticsSystem::PlayHapticEffect(HapticEffectType effectType, int controllerIndex, float duration, float strength, float secondaryStrength, bool overrideCurrentEffect)
{
	if (m_effectActive && overrideCurrentEffect)
	{
		EndCurrentEffect(effectType, controllerIndex);
	}

	m_currentEffect.m_type = effectType;
	m_currentEffect.m_duration = duration;
	m_currentEffect.m_strength = strength;
	m_currentEffect.m_secondaryStrength = secondaryStrength;

	switch (effectType)
	{
		case SimpleRumble:
			InitSimpleRumbleEffect(controllerIndex);
			PlaySimpleRumbleEffect(controllerIndex);
			break;

		case LeftRight:
			InitLeftRightEffect(controllerIndex);
			PlayLeftRightEffect(controllerIndex);
			break;
	}
}

void HapticsSystem::InitSimpleRumbleEffect(int controllerIndex)
{
	m_currentEffect.m_effectId = -1;
	SDL_HapticRumbleInit(m_hapticHandles[controllerIndex]);
}

void HapticsSystem::InitLeftRightEffect(int controllerIndex)
{
	SDL_HapticEffect effect;

	// Create the effect
	SDL_memset(&effect, 0, sizeof(SDL_HapticEffect)); // 0 is safe default
	effect.type = SDL_HAPTIC_LEFTRIGHT;
	effect.leftright.large_magnitude = m_currentEffect.m_strength;
	effect.leftright.small_magnitude = m_currentEffect.m_secondaryStrength;
	effect.leftright.length = m_currentEffect.m_duration;

	m_currentEffect.m_effectId = SDL_HapticNewEffect(m_hapticHandles[controllerIndex], &effect);
}

void HapticsSystem::PlaySimpleRumbleEffect(int controllerIndex)
{
	SDL_HapticRumblePlay(m_hapticHandles[controllerIndex], m_currentEffect.m_duration, m_currentEffect.m_strength);
}

void HapticsSystem::PlayLeftRightEffect(int controllerIndex)
{
	SDL_HapticRunEffect(m_hapticHandles[controllerIndex], m_currentEffect.m_effectId, 1);
}

void HapticsSystem::EndCurrentEffect(HapticEffectType effectType, int controllerIndex)
{
	switch (effectType)
	{
		case SimpleRumble:
			SDL_HapticRumbleStop(m_hapticHandles[controllerIndex]);
			break;

		case LeftRight:
			break;
	}
}