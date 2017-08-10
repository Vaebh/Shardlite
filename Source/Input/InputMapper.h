#ifndef INPUT_MAPPER_SHARDLITE
#define INPUT_MAPPER_SHARDLITE

#include "InputContext.h"
#include "MappedInput.h"
#include "../Systems/ISystem.h"

#include "InputCallback.h"

#include <vector>

#define MAX_CONTROLLERS 4

struct _SDL_GameController;
typedef struct _SDL_GameController SDL_GameController;

struct _SDL_Haptic;
typedef struct _SDL_Haptic SDL_Haptic;

class InputMapper : ISystem
{
public:
	int StartUp();
	int ShutDown();

	void UpdateInput();

	void AddContext(InputContext& in_context);
	void SubscribeToInput(IInputCallback* callback);

	inline int GetNumControllers() { return m_numControllers; }
	inline SDL_GameController** GetGameControllerHandles() { return m_controllerHandles; }

private:
	void SetupGameControllers();

	void GetRawInput(std::vector<MappedInput>& mappedInput);
	void MapRawInput(std::vector<MappedInput>& mappedInput);
	void ProcessMappedInput(std::vector<MappedInput>& mappedInput);

	void AddControllerTriggerInput(std::vector<MappedInput>& mappedInput);

	void AddRawKeyInput(std::vector<MappedInput>& mappedInput);

private:
	std::vector<InputContext> m_inputContexts;
	std::vector<IInputCallback*> m_inputCallbacks;

	RawInput m_previousInputState[NUM_EVENTS] = {};

	int m_numControllers;
	SDL_GameController* m_controllerHandles[MAX_CONTROLLERS];
	SDL_Haptic* m_rumbleHandles[MAX_CONTROLLERS];
};

#endif