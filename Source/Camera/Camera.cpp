#include "Camera.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtx\transform2.hpp>

const glm::vec3 WORLD_UP = glm::vec3(0.f, 1.f, 0.f);
const glm::vec3 WORLD_RIGHT = glm::vec3(1.f, 0.f, 0.f);

Camera::Camera()
{
	m_position = glm::vec3(0.f, 0.f, 0.f);

	m_direction = glm::vec3(0.f, 0.f, 1.f);
	m_right = glm::vec3(1.f, 0.f, 0.f);
	m_up = WORLD_UP;
}

void Camera::RotateYaw(float angle)
{
	glm::quat &rot = glm::angleAxis(glm::radians(angle), WORLD_UP);

	m_direction = m_direction * rot;
	m_right = glm::cross(m_direction, m_up);
}

void Camera::RotatePitch(float angle)
{
	glm::quat &rot = glm::angleAxis(glm::radians(angle), WORLD_RIGHT);

	m_direction = m_direction * rot;
	//m_up = glm::cross(m_right, m_direction);
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