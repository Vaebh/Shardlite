#ifndef INPUT_MAPPER_SHARDLITE
#define INPUT_MAPPER_SHARDLITE

#include "InputContext.h"
#include "MappedInput.h"
#include "../Systems/ISystem.h"

#include <vector>

#define MAX_CONTROLLERS 4

struct _SDL_GameController;
typedef struct _SDL_GameController SDL_GameController;

class InputMapper : ISystem
{
public:
	int StartUp();
	int ShutDown();

	void UpdateInput();

	void AddContext(InputContext& in_context);
	void SubscribeToInput(InputCallback callback);

private:
	void SetupGameControllers();

	void GetRawInput(std::vector<MappedInput>& mappedInput);
	void MapRawInput(std::vector<MappedInput>& mappedInput);
	void ProcessMappedInput(std::vector<MappedInput>& mappedInput);

private:
	std::vector<InputContext> m_inputContexts;
	std::vector<InputCallback> m_inputCallbacks;

	int m_numControllers;
	SDL_GameController* m_controllerHandles[MAX_CONTROLLERS];
};

#endif