#ifndef CAMERA_SYSTEM_SHARDLITE
#define CAMERA_SYSTEM_SHARDLITE

#include "../Systems/ISystem.h"
#include "../Camera/Camera.h"

#define MAX_CAMERAS 4

class CameraSystem : public ISystem
{
public:
	int StartUp();
	int ShutDown();

	bool AddCamera(Camera& in_newCamera, bool makeActive = true);

	void MakeCameraActive(int in_cameraIndex);

private:
	int m_numCameras = 0;
	Camera m_activeCameras[MAX_CAMERAS];

	Camera* m_activeCamera;
};

#endif