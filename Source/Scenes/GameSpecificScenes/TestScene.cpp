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

	Entity CreateCameraEntity()
	{
		Entity entity;
		entity._scale = glm::vec3(1.f, 1.f, 1.f);

		entity._position = glm::vec3(8.f, 18.65f, 24.18f);

		return entity;
	}
}

TestScene::TestScene() :
	Scene()
{

}

int testMeshCompIndex = -1;

void TestScene::SetupScene()
{
	m_testEntity = CreateTestEntity();

	int shaderId;
	GLuint shaderProgram = m_shaderCache->AddShader("Assets/Shaders/3DVertexShader.txt", "Assets/Shaders/3DFragShader.txt", shaderId);
	Shader* default3dShader = m_shaderCache->GetShader(shaderId);

	m_meshCompIndex = m_meshCompManager->AddMeshComponent(&m_testEntity, "TestAssets/skeleton.fbx", default3dShader);
	testMeshCompIndex = m_meshCompManager->AddMeshComponent(&m_testEntity, "TestAssets/cube.fbx", default3dShader);

	m_textureManager->RequestTexture("Assets/Textures/TestAssets/skeleton.png");

	m_cameraEntity = CreateCameraEntity();

	m_flyCamPointer = (FlyCamera*)(m_cameraEntity.AddComponent<FlyCamera>());

	m_flyCamPointer->SetManagerReferences(m_inputMapper, m_gameWindow);
	m_flyCamPointer->m_position = glm::vec3(8.f, 18.65f, 24.18f);
	m_flyCamPointer->m_direction = glm::vec3(0.f, 0.f, -1.f);
	m_flyCamPointer->m_inverted = false;

	//m_gameCamera = FlyCamera();
	//m_gameCamera.SetManagerReferences(m_inputMapper, m_gameWindow);
	////m_gameCamera.m_position = glm::vec3(0.23f, 1.65f, 4.18f);
	//m_gameCamera.m_position = glm::vec3(8.f, 18.65f, 24.18f);
	//m_gameCamera.m_direction = glm::vec3(0.f, 0.f, -1.f);
	//m_gameCamera.m_inverted = false;
	//GameCamera.RotateYaw(180.f);
	//GameCamera.m_direction = glm::vec3(-1.f, -0.f, 0.f);

	m_inputCallback.SetArgs(this, &TestScene::HandleInput);
	m_inputMapper->SubscribeToInput(&m_inputCallback);

	//m_inputCallbackFree.SetArgs(&TestInputFreeFunc);
	//m_inputMapper->SubscribeToInput(&m_inputCallbackFree);

	m_testInputContext.PopulateInputMap();
	m_inputMapper->AddContext(m_testInputContext);
}

void TestInputFreeFunc(MappedInput& mappedInput)
{
	if (mappedInput.m_rawInput == INPUT_CONTROLLER_BUTTON_B_PRESSED)
	{
		std::cout << "b pressed" << std::endl;
	}
}

void TestScene::HandleInput(MappedInput& mappedInput)
{
	if (mappedInput.m_rawInput == INPUT_LEFT_CLICK_PRESS)
	{
		std::cout << "left click pressed" << std::endl;
	}

	if (mappedInput.m_rawInput == INPUT_LEFT_CLICK_RELEASE)
	{
		std::cout << "left click released" << std::endl;
	}

	if (mappedInput.m_rawInput == INPUT_CONTROLLER_BUTTON_B_PRESSED)
	{
		m_hapticsSystem->PlayHapticEffect(SimpleRumble, 0, 500.f, 1.f, 0.f, false);
	}

	if (mappedInput.m_rawInput == INPUT_CONTROLLER_BUTTON_Y_PRESSED)
	{
		//m_testEntity._position += glm::vec3(0.f, 0.f, 0.2f);

		std::cout << "Y button pressed" << std::endl;
	}

	if (mappedInput.m_rawInput == INPUT_CONTROLLER_BUTTON_Y_HELD)
	{
		std::cout << "Y button held" << std::endl;
	}

	if (mappedInput.m_rawInput == INPUT_CONTROLLER_BUTTON_Y_RELEASED)
	{
		std::cout << "Y button released" << std::endl;
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_ESCAPE_PRESSED)
	{
		Application::Quit();
		return;
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_2_PRESSED)
	{
		m_testEntity._position = glm::vec3(0.f, 0.f, 2.f);
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_3_PRESSED)
	{
		m_testEntity._position = glm::vec3(0.f, 0.f, 3.f);
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_4_PRESSED)
	{
		m_testEntity._position = glm::vec3(0.f, 0.f, 4.f);
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_5_PRESSED)
	{
		m_testEntity._position = glm::vec3(0.f, 0.f, 5.f);
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_6_PRESSED)
	{
		m_testEntity._rotation *= glm::angleAxis(1.f, glm::vec3(0.f, 1.f, 0.f));
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_7_PRESSED)
	{
		m_testEntity._rotation *= glm::angleAxis(-1.f, glm::vec3(0.f, 1.f, 0.f));
	}

	if (mappedInput.m_rawInput == INPUT_SCANCODE_BACKSPACE_PRESSED)
	{
		std::cout << "Cam pos: " << m_gameCamera.m_position.x << ", " << m_gameCamera.m_position.y << ", " << m_gameCamera.m_position.z << std::endl;
	}
}

void TestScene::ShutdownScene()
{

}

void TestScene::Update(float deltaTime)
{
	//m_gameCamera.Update(deltaTime);
	m_flyCamPointer->Update(deltaTime);

	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, m_testEntity._position) * glm::mat4_cast(m_testEntity._rotation) * glm::scale(model, m_testEntity._scale);

	MeshComponent* meshComp = m_meshCompManager->RequestMeshComponentByIndex(m_meshCompIndex);
	meshComp->SetUniformData(Model, model);
	meshComp->SetUniformData(View, /*m_gameCamera.*/m_flyCamPointer->CalculateViewMatrix());

	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(8.f, 18.65f, 15.18f)) * glm::mat4_cast(m_testEntity._rotation) * glm::scale(model, m_testEntity._scale);

	MeshComponent* testMeshComp = m_meshCompManager->RequestMeshComponentByIndex(testMeshCompIndex);
	testMeshComp->SetUniformData(Model, model);
	testMeshComp->SetUniformData(View, m_flyCamPointer->CalculateViewMatrix());
}