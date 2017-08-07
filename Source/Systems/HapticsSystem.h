#ifndef HAPTICS_SYSTEM_SHARDLITE
#define HAPTICS_SYSTEM_SHARDLITE

#include "ISystem.h"

#define MAX_CONTROLLERS 4

struct _SDL_GameController;
typedef struct _SDL_GameController SDL_GameController;

struct _SDL_Haptic;
typedef struct _SDL_Haptic SDL_Haptic;

enum HapticEffectType
{
	Invalid,
	SimpleRumble,
	LeftRight
};

struct HapticEffect
{
	HapticEffectType m_type;
	float m_duration;
	float m_strength;
	float m_secondaryStrength;

	int m_effectId = -1;
	int m_controllerIndex = -1;

	HapticEffect()
	{
		m_type = Invalid;
		m_duration = 0.f;
		m_strength = 0.f;
		m_secondaryStrength = 0.f;

		m_effectId = 0;
		m_controllerIndex = 0;
	}
};

class HapticsSystem : ISystem
{
public:
	int StartUp();
	int ShutDown();

	void SetHapticHandles(SDL_GameController* in_controllerHandles[MAX_CONTROLLERS], int numControllers);

	void Update(float deltaTime);

	void PlayHapticEffect(HapticEffectType effectType, int controllerIndex, float duration, float strength, float secondaryStrength, bool overrideCurrentEffect);

	void InitSimpleRumbleEffect(int controllerIndex);
	void InitLeftRightEffect(int controllerIndex);

	void PlaySimpleRumbleEffect(int controllerIndex);
	void PlayLeftRightEffect(int controllerIndex);

private:
	void EndCurrentEffect(HapticEffectType effectType, int controllerIndex);

private:
	SDL_Haptic* m_hapticHandles[MAX_CONTROLLERS];

	bool m_effectActive;
	HapticEffect m_currentEffect;
};

#endif