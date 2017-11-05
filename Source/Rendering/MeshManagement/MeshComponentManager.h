#ifndef MESH_COMPONENT_MANAGER_SHARDLITE
#define MESH_COMPONENT_MANAGER_SHARDLITE

#include "MeshComponent.h"

#include "../../Systems/ISystem.h"

#include <vector>

// At some point in the future maybe add two different lists for each
// batch type, one for static and for dynamic things

class Shader;

class MeshComponentManager : ISystem
{
public:
	MeshComponentManager() {}
	~MeshComponentManager() {}

	MeshComponentManager(const MeshComponentManager& meshComp) =delete;
	MeshComponentManager& operator=(const MeshComponentManager& meshComp) =delete;

	int AddMeshComponent(Entity* parentEntity, const char* meshName, Shader* meshShader);
	int RequestMeshComponent(const char* meshName);

	// Pointers returned from this function should not be kept for long, as thhey may become
	// invalid if/when the vector resizes
	MeshComponent* RequestMeshComponentByIndex(int index);

	std::vector<MeshComponent>& GetMeshComponents() { return m_meshComponents; }

	int StartUp();
	int ShutDown();

private:
	std::vector<MeshComponent> m_meshComponents;
};

#endif
