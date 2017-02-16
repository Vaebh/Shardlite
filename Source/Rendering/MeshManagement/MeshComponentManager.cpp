#include "MeshComponentManager.h"
#include "../System/Batch.h"
#include "../../EntityComponent/Entity.h"
#include "MeshAssetManager.h"

//bool MeshComponentManager::GenerateBatches(std::vector<Batch>& opaqueBatches, std::vector<Batch>& transparentBatches, std::vector<Batch>& spriteBatches)
//{
//	if (m_meshComponents.empty())
//	{
//		return false;
//	}
//
//	opaqueBatches.clear();
//	transparentBatches.clear();
//	spriteBatches.clear();
//
//	for (int i = 0; i < m_meshComponents.size(); ++i)
//	{
//		if (m_meshComponents[i].IsTransparent())
//		{
//			//transparentBatches.push_back(m_meshComponents[i]);
//			continue;
//		}
//
//		// How do I detect sprites?
//		/*if (isSprite)
//		{
//			continue;
//		}*/
//		
//		//opaqueBatches.push_back();
//	}
//
//	return true;
//}

MeshComponent* MeshComponentManager::AddMeshComponent(Entity* parentEntity, const char* meshName)
{
	if (parentEntity == nullptr)
	{
		return nullptr;
	}

	Mesh* mesh = MeshAssetManager::GetMesh(meshName);
	if (mesh == nullptr)
	{
		mesh = MeshAssetManager::LoadMesh(meshName);

		if (mesh == nullptr)
		{
			return nullptr;
		}
	}

	m_meshComponents.push_back(MeshComponent(mesh));

	// This would be the point I actually added it to the correct batch, but for now just stuffing it into opaque
	AddOpaqueMesh(m_meshComponents.back());

	return (&m_meshComponents.back());
}

// OKay so this is bad because I'm giving the batches pointers to elements in a vector
// Those pointers might become invalid when the vector resizes
// SO INSTEAD I am going to store their component ids and look them up when I need them
bool MeshComponentManager::AddOpaqueMesh(MeshComponent& newMeshComp)
{
	for (int i = 0; i < m_opaqueBatches.size(); ++i)
	{
		if (m_opaqueBatches[i].IsBatchCompatible(newMeshComp.GetShaderId(), newMeshComp.GetTextureIds()))
		{
			m_opaqueBatches[i].AddMesh(&newMeshComp);
			return true;
		}
	}

	m_opaqueBatches.push_back(Batch(&newMeshComp));
	return true;
}