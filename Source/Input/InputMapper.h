#ifndef INPUT_MAPPER_SHARDLITE
#define INPUT_MAPPER_SHARDLITE

#include "InputContext.h"
#include "MappedInput.h"
#include "../Systems/ISystem.h"

#include <vector>

class InputMapper : ISystem
{
public:
	int StartUp();
	int ShutDown();

	void UpdateInput();

	void GetRawInput(MappedInput& mappedInput);
	void MapRawInput(MappedInput& mappedInput);
	void ProcessMappedInput(MappedInput& mappedInput);

	void AddContext(InputContext& in_context);
	void SubscribeToInput(InputCallback callback);

private:
	std::vector<InputContext> m_inputContexts;
	std::vector<InputCallback> m_inputCallbacks;
};

#endif