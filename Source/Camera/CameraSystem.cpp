#include "CameraSystem.h"

#include "../Systems/SetupUtils.h"

int CameraSystem::StartUp()
{
	return SETUP_SUCCESS;
}

int CameraSystem::ShutDown()
{
	return SETUP_SUCCESS;
}

bool CameraSystem::AddCamera(Camera& in_newCamera, bool makeActive)
{
	if (m_numCameras >= MAX_CAMERAS)
	{
		return false;
	}

	m_activeCameras[m_numCameras] = in_newCamera;

	if (makeActive)
	{
		m_activeCamera = &m_activeCameras[m_numCameras];
	}

	++m_numCameras;

	return true;
}

void CameraSystem::MakeCameraActive(int in_cameraIndex)
{
	if (in_cameraIndex >= MAX_CAMERAS)
	{
		return;
	}

	m_activeCamera = &m_activeCameras[m_numCameras];
}