#include "Application.h"

bool Application::m_quitFlag = false;

void Application::StartUpSystems()
{
	int setupSuccess = -1;
	
	m_sdlHandler.StartUp();

	setupSuccess = m_renderSystem.StartUp();
	setupSuccess = m_meshComponentManager.StartUp();

	m_renderSystem.SetManagerReferences(&m_meshComponentManager);

	m_testScene.SetManagerReferences(&m_meshComponentManager, &m_shaderCache, &m_textureManager, m_sdlHandler.GetWindow());
	m_testScene.SetupScene();

	//if(setupSuccess != )
}

void Application::ShutDownSystems()
{
	m_sdlHandler.ShutDown();
	m_renderSystem.ShutDown();
}

bool Application::Update()
{
	m_testScene.Update();

	m_renderSystem.Draw();

	return m_quitFlag;
}

void Application::Quit()
{
	m_quitFlag = true;
}