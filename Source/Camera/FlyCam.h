#ifndef FLY_CAMERA_SHARDLITE
#define FLY_CAMERA_SHARDLITE

#include "Camera.h"

#include "../Input/InputCallback.h"

class SDL_Window;

class FlyCamera : public Camera
{
public:
	FlyCamera();

	void OnReferencesInitialized();
	void HandleInput(MappedInput& mappedInput);

	//void Update(float deltaTime);

private:
	float m_moveSpeed;
	float m_rotationSpeed;

	InputCallbackMember<FlyCamera> m_inputCallback;
};

#endif
