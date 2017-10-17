#include "Camera.h"
#include <gtx/transform.hpp>
#include <gtx/transform2.hpp>

#include "../Utils/VectorDefaults.h"

#include "../EntityComponent/Entity.h"

#include <iostream>

Camera::Camera() : m_inverted(true)
{
	m_position = glm::vec3(0.f, 0.f, 0.f);

	m_direction = glm::vec3(0.f, 0.f, 1.f);
	m_right = glm::vec3(1.f, 0.f, 0.f);
	m_up = VectorDefaults::VECTOR_Y_AXIS;
}

void Camera::SetManagerReferences(InputMapper* inputMapper, SDL_Window* window)
{
	m_inputMapper = inputMapper;
	m_window = window;

	OnReferencesInitialized();
}

void Camera::RotateYaw(float angle)
{
	glm::quat rot = glm::angleAxis(/*glm::radians(*/angle/*)*/, VectorDefaults::VECTOR_Y_AXIS);

	if (m_rotationConstraints.y != 0)
	{
		glm::vec3 tempRot = glm::normalize(m_direction * rot);
		if (glm::abs(tempRot.x) >= 0.97f)
		{
			//return;
		}
	}

	m_direction = glm::normalize(m_direction * rot);
	m_right = glm::normalize(m_right * rot);
	m_up = glm::normalize(m_up * rot);
}

void Camera::RotatePitch(float angle)
{
	glm::quat rot = glm::angleAxis(/*glm::radians(*/m_inverted ? -angle : angle/*)*/, m_right);

	if (m_rotationConstraints.x != 0)
	{
		glm::vec3 tempRot = glm::normalize(m_direction * rot);
		if (glm::abs(tempRot.y) >= 0.97f)
		{
			return;
		}
	}

	m_direction = glm::normalize(m_direction * rot);
	m_up = glm::normalize(m_up * rot);
}

glm::mat4 Camera::CalculateViewMatrix() const
{
	glm::mat4 viewMatrix = glm::lookAt(
		m_position,
		m_position + m_direction,
		VectorDefaults::VECTOR_Y_AXIS
		//m_up
	);

	return viewMatrix;
}

void Camera::Update(float deltaTime)
{
	if (m_entityRotation.x != m_parentEntity->_rotation.x ||
		m_entityRotation.y != m_parentEntity->_rotation.y ||
		m_entityRotation.z != m_parentEntity->_rotation.z ||
		m_entityRotation.w != m_parentEntity->_rotation.w)
	{
		glm::vec3 pitchAngleVec = glm::eulerAngles(m_parentEntity->_rotation);
		RotateYaw(pitchAngleVec.y);

		glm::vec3 yawAngleVec = glm::eulerAngles(m_parentEntity->_rotation);
		RotatePitch(yawAngleVec.x);

		m_entityRotation = m_parentEntity->_rotation;
	}
}