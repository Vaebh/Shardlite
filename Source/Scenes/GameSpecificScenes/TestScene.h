#ifndef TEST_SCENE_SHARDLITE
#define TEST_SCENE_SHARDLITE

#include "../Scene.h"

#include "../../EntityComponent/Entity.h"

#include "../../Camera/FlyCam.h"

#include "../../Input/InputCallback.h"

#include "../../Input/InputContext.h"

class MeshComponent;

class TestScene : public Scene
{
public:
	TestScene();

	virtual void SetupScene();
	virtual void Update(float deltaTime);
	virtual void ShutdownScene();

	void HandleInput(MappedInput& mappedInput);

private:
	FlyCamera m_gameCamera;
	FlyCamera* m_flyCamPointer;

	Entity m_testEntity;
	MeshComponent* m_meshComp;

	InputContext m_testInputContext;

	InputCallbackFree m_inputCallbackFree;
	InputCallbackMember<TestScene> m_inputCallback;
};

#endif