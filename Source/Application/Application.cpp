#include "Application.h"

void Application::StartUpSystems()
{
	int setupSuccess = m_sdlHandler.StartUp();
	setupSuccess = m_renderSystem.StartUp();

	//if(setupSuccess != )
}

void Application::ShutDownSystems()
{
	m_sdlHandler.ShutDown();
	m_renderSystem.ShutDown();
}