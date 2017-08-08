#include "InputCallback.h"

void InputCallbackFree::SetArgs(void (*in_inputCallbackFunc)(MappedInput&))
{
	m_eventCallbackFunc = in_inputCallbackFunc;

	assert(m_eventCallbackFunc);
}

void InputCallbackFree::operator() (MappedInput& mappedInput)
{
	(*m_eventCallbackFunc)(mappedInput);
}