#ifndef CAMERA_SHARDLITE
#define CAMERA_SHARDLITE

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Camera
{
public:
	Camera();

	glm::mat4 CalculateViewMatrix();
	void RotateYaw(float angle);
	void RotatePitch(float angle);

	bool m_inverted;

	glm::vec3 m_position;

	glm::vec3 m_rotationConstraints;

	glm::vec3 m_direction;
	glm::vec3 m_up;
	glm::vec3 m_right;
};

#endif