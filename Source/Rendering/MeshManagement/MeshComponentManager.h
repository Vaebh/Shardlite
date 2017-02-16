#ifndef MESH_COMPONENT_MANAGER_SHARDLITE
#define MESH_COMPONENT_MANAGER_SHARDLITE

#include "MeshComponent.h"

#include <vector>

// At some point in the future maybe add two different lists for each
// batch type, one for static and for dynamic things

class Batch;

class MeshComponentManager
{
public:
	//bool GenerateBatches(std::vector<Batch>& opaqueBatches, std::vector<Batch>& transparentBatches, std::vector<Batch>& spriteBatches);

	MeshComponent* AddMeshComponent(Entity* parentEntity, const char* meshName);

	inline std::vector<Batch> GetOpaqueBatches() { return m_opaqueBatches; }

private:
	bool AddOpaqueMesh(MeshComponent& newMeshComp);

	std::vector<MeshComponent> m_meshComponents;
	std::vector<Batch> m_opaqueBatches;
};

#endif