#ifndef FLY_CAMERA_SHARDLITE
#define FLY_CAMERA_SHARDLITE

#include "Camera.h"

class FlyCamera : public Camera
{
public:
	FlyCamera();

	void Update(float deltaTime);

	float _moveSpeed;
	float _rotationSpeed;
};

#endif
