#include "Scene.h"

Scene::Scene()
{

}

void Scene::SetManagerReferences(MeshComponentManager* meshComponentManager,
	ShaderCache* shaderCache,
	TextureManager* textureManager,
	SDL_Window* gameWindow,
	InputMapper* inputMapper,
	HapticsSystem* hapticsSystem)
{
	m_meshCompManager = meshComponentManager;
	m_shaderCache = shaderCache;
	m_textureManager = textureManager;

	m_gameWindow = gameWindow;
	m_inputMapper = inputMapper;
	m_hapticsSystem = hapticsSystem;
}