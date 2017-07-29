#ifndef FLY_CAMERA_SHARDLITE
#define FLY_CAMERA_SHARDLITE

#include "Camera.h"

class SDL_Window;

class FlyCamera : public Camera
{
public:
	FlyCamera();
	void Init(SDL_Window* window);

	void Update(float deltaTime);

	float m_moveSpeed;
	float m_rotationSpeed;

private:
	SDL_Window* m_window;
};

#endif
