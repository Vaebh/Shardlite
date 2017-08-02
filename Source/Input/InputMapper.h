#ifndef INPUT_MAPPER_SHARDLITE
#define INPUT_MAPPER_SHARDLITE

#include "InputContext.h"
#include "MappedInput.h"

#include <vector>

class InputMapper
{
public:
	void GetRawInput(MappedInput& mappedInput);
	void MapInput();
	void MapRawInput(MappedInput& mappedInput);
	void ProcessMappedInput(MappedInput& mappedInput);

	std::vector<InputContext> m_inputContexts;
};

#endif