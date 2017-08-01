#include "Application.h"
#include "../Systems/SetupUtils.h"

#include "../Input/InputMapper.h"

#include <SDL.h>

bool Application::m_quitFlag = false;

InputMapper inputMapper;

bool Application::StartUpSystems()
{
	int setupSuccess = m_sdlHandler.StartUp();

	setupSuccess = m_renderSystem.StartUp();
	setupSuccess = m_meshComponentManager.StartUp();

	if (setupSuccess != SETUP_SUCCESS)
	{
		return false;
	}

	m_renderSystem.SetManagerReferences(&m_meshComponentManager, m_sdlHandler.GetWindow());

	m_testScene.SetManagerReferences(&m_meshComponentManager, &m_shaderCache, &m_textureManager, m_sdlHandler.GetWindow());
	m_testScene.SetupScene();

	m_last = 0.f;
	m_current = 0.f;
	m_deltaTime = 0.f;

	return true;
}

void Application::ShutDownSystems()
{
	m_sdlHandler.ShutDown();
	m_renderSystem.ShutDown();
}

bool Application::Update()
{
	m_last = m_current;
	m_current = SDL_GetPerformanceCounter();
	m_deltaTime = (double)((m_current - m_last) * 1000 / SDL_GetPerformanceFrequency());

	inputMapper.MapInput();

	m_testScene.Update(m_deltaTime);

	m_renderSystem.Draw();

	return m_quitFlag;
}

void Application::Quit()
{
	m_quitFlag = true;
}