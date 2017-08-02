#include "InputContext.h"

void InputContext::PopulateInputMap()
{
	// Test stuff
	m_mappedInputs[INPUT_MOUSE_MOTION] = MOVE_CAMERA;
}

bool InputContext::MapInput(MappedInput& mappedInput)
{
	if (m_mappedInputs.find(mappedInput.m_rawInput) == m_mappedInputs.end())
	{
		return false;
	}

	mappedInput.m_processedInput = m_mappedInputs[mappedInput.m_rawInput];

	return true;
}