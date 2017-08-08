#include "TestScene.h"

#include <SDL.h>

#include "../../Rendering/GLIncludes.h"

#include "../../Rendering/MeshManagement/Mesh.h"
#include "../../Rendering/MeshManagement/MeshComponentManager.h"

#include "../../Rendering/Shaders/Shader.h"
#include "../../Rendering/Shaders/ShaderCache.h"

#include "../../Rendering/AssetLoading/TextureManager.h"

#include "../../Application/Application.h"

#include "../../Input/MappedInput.h"
#include "../../Input/InputConstants.h"
#include "../../Input/InputMapper.h"

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

TestScene::TestScene()
{

}

void TestInputFreeFunc(MappedInput& mappedInput)
{
	if (mappedInput.m_rawInput == INPUT_CONTROLLER_BUTTON_B)
	{
		std::cout << "b pressed" << std::endl;
	}
}

void TestScene::SetupScene()
{
	m_testEntity = CreateTestEntity();

	int shaderId;
	GLuint shaderProgram = m_shaderCache->AddShader("Assets/Shaders/3DVertexShader.txt", "Assets/Shaders/3DFragShader.txt", shaderId);
	Shader* default3dShader = m_shaderCache->GetShader(shaderId);

	m_meshComp = m_meshCompManager->AddMeshComponent(&m_testEntity, "TestAssets/skeleton.fbx", default3dShader);

	m_textureManager->RequestTexture("Assets/Textures/TestAssets/skeleton.png");

	m_gameCamera = FlyCamera();
	m_gameCamera.Init(m_gameWindow);
	//m_gameCamera.m_position = glm::vec3(0.23f, 1.65f, 4.18f);
	m_gameCamera.m_position = glm::vec3(8.f, 18.65f, 24.18f);
	m_gameCamera.m_direction = glm::vec3(0.f, 0.f, -1.f);
	m_gameCamera.m_inverted = false;
	//GameCamera.RotateYaw(180.f);
	//GameCamera.m_direction = glm::vec3(-1.f, -0.f, 0.f);

	m_inputCallback.SetArgs(this, &TestScene::HandleInput);
	m_inputMapper->SubscribeToInput(&m_inputCallback);

	//m_inputCallbackFree.SetArgs(&TestInputFreeFunc);
	//m_inputMapper->SubscribeToInput(&m_inputCallbackFree);

	m_testInputContext.PopulateInputMap();
	m_inputMapper->AddContext(m_testInputContext);
}

void TestScene::HandleInput(MappedInput& mappedInput)
{
	if (mappedInput.m_processedInput == MOVE_CAMERA)
	{
		m_gameCamera.RotatePitch(glm::radians((float)(mappedInput.m_rangeInputValue.y)* 100.f));
		m_gameCamera.RotateYaw(glm::radians((float)(mappedInput.m_rangeInputValue.x)* 100.f));
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_W)
	{
		m_testEntity._position += glm::vec3(0.f, 0.f, 0.2f);
	}

	if (mappedInput.m_rawInput == INPUT_LEFT_CLICK_PRESS)
	{
		std::cout << "left click" << std::endl;
	}

	/*if (mappedInput.m_rawInput == INPUT_CONTROLLER_BUTTON_B)
	{
		std::cout << "b pressed" << std::endl;
	}*/

	if (mappedInput.m_rawInput == INPUT_CONTROLLER_LEFT_TRIGGER)
	{
		//std::cout << "left trigger: " << mappedInput.m_inputValue << std::endl;
	}

	if (mappedInput.m_rawInput == INPUT_CONTROLLER_BUTTON_B)
	{
		m_hapticsSystem->PlayHapticEffect(SimpleRumble, 0, 500.f, 1.f, 0.f, false);
	}

	if (mappedInput.m_rawInput == INPUT_CONTROLLER_BUTTON_Y)
	{
		m_hapticsSystem->PlayHapticEffect(LeftRight, 0, 1000.f, 32000.f, 1000.f, false);
	}
}

void TestScene::ShutdownScene()
{

}

void TestScene::Update(float deltaTime)
{
	m_gameCamera.Update(deltaTime);

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

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

	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, m_testEntity._position) * glm::mat4_cast(m_testEntity._rotation) * glm::scale(model, m_testEntity._scale);

	m_meshComp->BindUniformData(Model, model);
	m_meshComp->BindUniformData(View, m_gameCamera.CalculateViewMatrix());
}