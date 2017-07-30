#include "TestScene.h"

#include <SDL.h>

#include "../../Rendering/GLIncludes.h"

#include "../../Rendering/MeshManagement/Mesh.h"
#include "../../Rendering/MeshManagement/MeshComponentManager.h"

#include "../../Rendering/Shaders/Shader.h"
#include "../../Rendering/Shaders/ShaderCache.h"

#include "../../Rendering/AssetLoading/TextureManager.h"

#include "../../Application/Application.h"

#include <iostream>

namespace
{
	Entity CreateTestEntity()
	{
		Entity entity;

		// Humanoid Scale
		//entity._scale = glm::vec3(0.1f, 0.1f, 0.1f);

		// Skeleton Scale
		entity._scale = glm::vec3(1.f, 1.f, 1.f);

		//entity._position = glm::vec3(0.f, 0.f, 5.f);

		entity._rotation = entity._rotation * glm::angleAxis(1.f, glm::vec3(-80.f, 0.f, 0.f));

		return entity;
	}
}

void TestScene::SetupScene()
{
	m_testEntity = CreateTestEntity();

	int shaderId;
	GLuint shaderProgram = m_shaderCache->AddShader("Assets/Shaders/3DVertexShader.txt", "Assets/Shaders/3DFragShader.txt", shaderId);
	Shader* default3dShader = m_shaderCache->GetShader(shaderId);

	m_meshComp = m_meshCompManager->AddMeshComponent(&m_testEntity, "skeleton.fbx", default3dShader);

	m_textureManager->RequestTexture("Assets/Textures/skeleton.png");

	m_gameCamera = FlyCamera();
	m_gameCamera.Init(m_gameWindow);
	//m_gameCamera.m_position = glm::vec3(0.23f, 1.65f, 4.18f);
	m_gameCamera.m_position = glm::vec3(8.f, 18.65f, 24.18f);
	m_gameCamera.m_direction = glm::vec3(0.f, 0.f, -1.f);
	m_gameCamera.m_inverted = false;
	//GameCamera.RotateYaw(180.f);
	//GameCamera.m_direction = glm::vec3(-1.f, -0.f, 0.f);
}

void TestScene::ShutdownScene()
{

}

void TestScene::Update(float deltaTime)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	m_gameCamera.Update(deltaTime);

	glm::mat4 model = glm::mat4(1);

	if (keystate[SDL_SCANCODE_UP])
	{
		model = glm::translate(model, m_testEntity._position += glm::vec3(0.f, 0.f, 0.1f)) * glm::mat4_cast(m_testEntity._rotation) * glm::scale(model, m_testEntity._scale);
	}

	if (keystate[SDL_SCANCODE_ESCAPE])
	{
		Application::Quit();
		return;
	}

	if (keystate[SDL_SCANCODE_2])
	{
		m_testEntity._position = glm::vec3(0.f, 0.f, 2.f);
	}

	if (keystate[SDL_SCANCODE_3])
	{
		m_testEntity._position = glm::vec3(0.f, 0.f, 3.f);
	}

	if (keystate[SDL_SCANCODE_4])
	{
		m_testEntity._position = glm::vec3(0.f, 0.f, 4.f);
	}

	if (keystate[SDL_SCANCODE_5])
	{
		m_testEntity._position = glm::vec3(0.f, 0.f, 5.f);
	}

	if (keystate[SDL_SCANCODE_6])
	{
		m_testEntity._rotation *= glm::angleAxis(1.f, glm::vec3(0.f, 1.f, 0.f));
	}

	if (keystate[SDL_SCANCODE_BACKSPACE])
	{
		std::cout << "Cam pos: " << m_gameCamera.m_position.x << ", " << m_gameCamera.m_position.y << ", " << m_gameCamera.m_position.z << std::endl;
	}

	model = glm::mat4(1);
	model = glm::translate(model, m_testEntity._position) * glm::mat4_cast(m_testEntity._rotation) * glm::scale(model, m_testEntity._scale);

	m_meshComp->BindUniformData(Model, model);
	m_meshComp->BindUniformData(View, m_gameCamera.CalculateViewMatrix());

}