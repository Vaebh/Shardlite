#ifndef CAMERA_SHARDLITE
#define CAMERA_SHARDLITE

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class InputMapper;
class MappedInput;
class SDL_Window;

class Camera
{
public:
	Camera();

	void SetManagerReferences(InputMapper* inputMapper, SDL_Window* window);

	virtual void OnReferencesInitialized() {}

	glm::mat4 CalculateViewMatrix() const;
	void RotateYaw(float angle);
	void RotatePitch(float angle);

	inline void SetPosition(glm::vec3 in_newPosition) { m_position = in_newPosition; }

public:
	bool m_inverted;

	glm::vec3 m_position;

	glm::vec3 m_rotationConstraints;

	glm::vec3 m_direction;
	glm::vec3 m_up;
	glm::vec3 m_right;

	InputMapper* m_inputMapper;
	SDL_Window* m_window;
};

#endif
