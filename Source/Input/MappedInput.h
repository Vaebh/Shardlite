#ifndef MAPPED_INPUT_SHARDLITE
#define MAPPED_INPUT_SHARDLITE

#include "RawInputConstants.h"
#include "InputConstants.h"

#include <glm.hpp>

enum InputType
{
	KeyDown,
	KeyUp,
	KeyHeld,
	Range
};

struct MappedInput
{
	RawInput m_rawInput;
	Input m_processedInput;
	InputType m_inputType;

	int m_intInputValue;
	glm::vec2 m_rangeInputValue;
};

typedef void(*InputCallback)(MappedInput& mappedInput);

#endif