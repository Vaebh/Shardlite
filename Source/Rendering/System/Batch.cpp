#include "Batch.h"
#include "../MeshManagement/Mesh.h"
#include "../MeshManagement/MeshComponent.h"
#include "../MeshManagement/MeshAssetManager.h"

#include <iostream>

Batch::Batch(MeshComponent* initialMeshComp)
{
	m_batchMeshIds.push_back(initialMeshComp->GetComponentId());

	m_shaderId = initialMeshComp->GetShaderId();
	m_textureIds = initialMeshComp->GetTextureIds();
}

bool Batch::IsBatchCompatible(int shaderId, std::vector<int> textureIds)
{
	if (shaderId != m_shaderId || textureIds != m_textureIds)
	{
		return false;
	}

	return true;
}

bool Batch::IsMeshInBatch(MeshComponent* mesh)
{
	if (mesh == nullptr)
	{
		return false;
	}

	for (int i = 0; i < m_batchMeshIds.size(); ++i)
	{
		if (mesh->GetComponentId() == m_batchMeshIds[i])
		{
			return true;
		}
	}

	return false;
}

bool Batch::AddMesh(MeshComponent* newMesh)
{
	if (newMesh == nullptr ||
		!IsBatchCompatible(newMesh->GetShaderId(), newMesh->GetTextureIds()) ||
		IsMeshInBatch(newMesh))
	{
		return false;
	}

	m_batchMeshIds.push_back(newMesh->GetComponentId());

	return true;
}

bool Batch::UpdateMesh(int meshId)
{
	std::cout << "UpdateMesh not implemented yet" << std::endl;
	return false;
}

void Batch::GenerateBatchData()
{
	m_vertexInfo.clear();

	// This isn't great, redo later
	std::map<int, Mesh*> allMeshes = MeshAssetManager::GetMeshes();
	for (int i = 0; i < m_batchMeshIds.size(); ++i)
	{
		if (allMeshes.find(m_batchMeshIds[i]) == allMeshes.end())
		{
			// TODO - mark for removal
			continue;
		}

		Mesh* mesh = allMeshes[m_batchMeshIds[i]];
		if (mesh == nullptr)
		{
			// TODO - not a great sign if null at this point, mark for removal from assets, rebuild all batches
			continue;
		}
		// This is bad, shouldn't be copying this data all over the place
		std::vector<GLfloat> newVerts = mesh->GetVertices();

		// Need to resize
		if ((m_vertexInfo.size() + newVerts.size()) > m_vertexInfo.capacity())
		{
			m_vertexInfo.resize(m_vertexInfo.size() + newVerts.size());
		}
		memcpy(&m_vertexInfo[m_vertexInfo.size()], &newVerts[0], newVerts.size());
	}
}

//bool UpdateMesh(int meshId);