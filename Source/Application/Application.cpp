#include "Application.h"

void Application::StartUpSystems()
{
	int setupSuccess = m_sdlHandler.StartUp();
	//if(setupSuccess != )
}

void Application::ShutDownSystems()
{
	m_sdlHandler.ShutDown();
}