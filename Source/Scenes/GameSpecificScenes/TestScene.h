#ifndef TEST_SCENE_SHARDLITE
#define TEST_SCENE_SHARDLITE

#include "../Scene.h"

#include "../../EntityComponent/Entity.h"

#include "../../Camera/FlyCam.h"

class MeshComponent;

class TestScene : public Scene
{
public:
	TestScene();

	virtual void SetupScene();
	virtual void Update(float deltaTime);
	virtual void ShutdownScene();

private:
	FlyCamera m_gameCamera;

	Entity m_testEntity;
	MeshComponent* m_meshComp;
};

#endif