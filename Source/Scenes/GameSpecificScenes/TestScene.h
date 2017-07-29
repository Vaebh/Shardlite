#ifndef TEST_SCENE_SHARDLITE
#define TEST_SCENE_SHARDLITE

#include "../Scene.h"

#include "../../EntityComponent/Entity.h"

#include "../../Camera/FlyCam.h"

class MeshComponent;

class TestScene : public Scene
{
public:
	virtual void SetupScene();
	virtual void Update();
	virtual void ShutdownScene();

private:
	double m_last = 0.f;
	double m_current = 0.f;
	double m_deltaTime = 0.f;

	FlyCamera m_gameCamera;

	Entity m_testEntity;
	MeshComponent* m_meshComp;
};

#endif