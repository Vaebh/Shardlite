#include "Camera.h"
#include <gtx/transform.hpp>
#include <gtx/transform2.hpp>

#include "../Utils/VectorDefaults.h"

#include <iostream>

Camera::Camera() : m_inverted(true)
{
	m_position = glm::vec3(0.f, 0.f, 0.f);

	m_direction = glm::vec3(0.f, 0.f, 1.f);
	m_right = glm::vec3(1.f, 0.f, 0.f);
	m_up = VectorDefaults::VECTOR_Y_AXIS;
}

void Camera::RotateYaw(float angle)
{
	glm::quat rot = glm::angleAxis(glm::radians(angle), VectorDefaults::VECTOR_Y_AXIS);

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
	glm::quat rot = glm::angleAxis(glm::radians(m_inverted ? -angle : angle), m_right);

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

glm::mat4 Camera::CalculateViewMatrix()
{
	glm::mat4 viewMatrix = glm::lookAt(
		m_position,
		m_position + m_direction,
		m_up
	);

	return viewMatrix;
}
