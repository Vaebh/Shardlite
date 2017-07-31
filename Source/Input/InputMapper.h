#ifndef INPUT_MAPPER_SHARDLITE
#define INPUT_MAPPER_SHARDLITE

#include "InputContext.h"

#include <vector>

class InputMapper
{
public:
	void DetectInput();
	void MapInputs();

	std::vector<InputContext> m_inputContexts;
};

#endif