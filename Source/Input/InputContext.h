#ifndef INPUT_CONTEXT_SHARDLITE
#define INPUT_CONTEXT_SHARDLITE

#include "RawInputConstants.h"
#include "InputConstants.h"
#include "MappedInput.h"

#include <map>

class InputContext
{
public:
	bool MapInput(MappedInput& mappedInput);
	//bool ProcessInput(MappedInput& mappedInput);

private:
	std::map<RawInput, Input> m_mappedInputs;
};

#endif