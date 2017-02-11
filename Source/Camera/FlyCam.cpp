#include "FlyCam.h"
#include <SDL.h>

#include <iostream>

FlyCamera::FlyCamera() :
Camera(),
_moveSpeed(0.005f)
{
	m_rotationConstraints = glm::vec3(0.97f, 0.f, 0.f);
}

void FlyCamera::Update(float deltaTime)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_W])
	{
		m_position += m_direction * (_moveSpeed * deltaTime);
	}
	if (keystate[SDL_SCANCODE_S])
	{
		m_position -= m_direction * (_moveSpeed * deltaTime);
	}
	if (keystate[SDL_SCANCODE_A])
	{
		m_position += m_right * (_moveSpeed * deltaTime);
	}
	if (keystate[SDL_SCANCODE_D])
	{
		m_position -= m_right * (_moveSpeed * deltaTime);
	}

	if (keystate[SDL_SCANCODE_SPACE])
	{
		m_position -= m_up * ((m_inverted ? -1.f : 1.f) * _moveSpeed * deltaTime);
	}

	//std::cout << "Direction: " << m_direction.x << ", " << m_direction.y << ", " << m_direction.z << std::endl;
	//std::cout << "Right: " << m_right.x << ", " << m_right.y << ", " << m_right.z << std::endl;
	//std::cout << "Up: " << m_up.x << ", " << m_up.y << ", " << m_up.z << std::endl << std::endl;
}