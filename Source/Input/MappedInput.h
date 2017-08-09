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
	ProcessedInput m_processedInput;
	InputType m_inputType;

	float m_inputValue;
	glm::vec2 m_rangeInputValue;
};

#endif