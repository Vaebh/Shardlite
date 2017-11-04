#ifndef INPUT_CONTEXT_SHARDLITE
#define INPUT_CONTEXT_SHARDLITE

#include "RawInputConstants.h"
#include "InputConstants.h"
#include "MappedInput.h"

#include <map>

class InputContext
{
public:
	InputContext();
	virtual ~InputContext() {}

	virtual void PopulateInputMap();
	bool MapInput(MappedInput& mappedInput);

private:
	std::map<RawInput, ProcessedInput> m_mappedInputs;
};

#endif