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
	MeshComponent* AddMeshComponent(Entity* parentEntity, const char* meshName);

	inline std::vector<Batch> GetOpaqueBatches() { return m_opaqueBatches; }
    inline std::vector<Batch> GetTransparentBatches() { return m_transparentBatches; }
    inline std::vector<Batch> GetOpaqueSpriteBatches() { return m_opaqueSpriteBatches; }
    inline std::vector<Batch> GetTransparentSpriteBatches() { return m_transparentSpriteBatches; }

private:
    void AddMeshToBatch(MeshComponent& meshComp);
    
	void AddOpaqueMesh(MeshComponent& newMeshComp);
    void AddTransparentMesh(MeshComponent& newMeshComp);

	std::vector<MeshComponent> m_meshComponents;
    
	std::vector<Batch> m_opaqueBatches;
    std::vector<Batch> m_transparentBatches;
    std::vector<Batch> m_opaqueSpriteBatches;
    std::vector<Batch> m_transparentSpriteBatches;
};

#endif
