#include "FlyCam.h"

#include "../Input/MappedInput.h"
#include "../Input/InputMapper.h"

#include <SDL.h>

#include <iostream>

FlyCamera::FlyCamera() :
Camera(),
m_moveSpeed(0.005f),
m_rotationSpeed(100.f)
{
	m_rotationConstraints = glm::vec3(0.97f, 0.f, 0.f);
    
#ifdef __APPLE__
    m_moveSpeed *= 0.1f;
    m_rotationSpeed *= 0.1f;
#endif
}

void FlyCamera::OnReferencesInitialized()
{
	m_inputCallback.SetArgs(this, &FlyCamera::HandleInput);
	m_inputMapper->SubscribeToInput(&m_inputCallback);
}

void FlyCamera::HandleInput(MappedInput& mappedInput)
{
	if (mappedInput.m_processedInput == ROTATE_CAMERA)
	{
		RotatePitch(glm::radians((float)(mappedInput.m_rangeInputValue.y)* 100.f));
		RotateYaw(glm::radians((float)(mappedInput.m_rangeInputValue.x)* 100.f));
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_W_PRESSED || mappedInput.m_rawInput == INPUT_SCANCODE_W_HELD)
	{
		m_position += m_direction * (m_moveSpeed * 100.f) * (m_inverted ? -1.f : 1.f);
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_S_PRESSED || mappedInput.m_rawInput == INPUT_SCANCODE_S_HELD)
	{
		m_position -= m_direction * (m_moveSpeed * 100.f) * (m_inverted ? -1.f : 1.f);
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_A_PRESSED || mappedInput.m_rawInput == INPUT_SCANCODE_A_HELD)
	{
		m_position += m_right * (m_moveSpeed * 100.f) * (m_inverted ? 1.f : -1.f);
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_D_PRESSED || mappedInput.m_rawInput == INPUT_SCANCODE_D_HELD)
	{
		m_position -= m_right * (m_moveSpeed * 100.f) * (m_inverted ? 1.f : -1.f);
	}
}

void FlyCamera::Update(float deltaTime)
{

}
