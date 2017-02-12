#ifndef FLY_CAMERA_SHARDLITE
#define FLY_CAMERA_SHARDLITE

#include "Camera.h"
#include <SDL.h>

class FlyCamera : public Camera
{
public:
	FlyCamera(SDL_Window* window);

	void Update(float deltaTime);

	float m_moveSpeed;
	float m_rotationSpeed;

private:
	SDL_Window* m_window;
};

#endif
