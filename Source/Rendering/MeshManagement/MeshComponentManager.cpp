#include "MeshComponentManager.h"
#include "../System/Batch.h"
#include "../../EntityComponent/Entity.h"
#include "MeshAssetManager.h"

// Extract AttributeType from ShaderParser
#include "../Shaders/ShaderParser.h"

namespace
{
	void BindAttributeDataToComponent(AttributeType attributeType, std::vector<GLfloat>& vertexData, MeshComponent* meshComp, Mesh* mesh, Shader* shader)
	{
		VertexAttribute& vertexAttribute = shader->m_vertexAttributes[attributeType];
		if (vertexData.size() > 0 && vertexAttribute.m_isValidAttribute)
		{
			meshComp->BindVertexData(attributeType, vertexAttribute, vertexData);
		}
	}

	void BindVertexAttributes(MeshComponent* meshComp)
	{
		Mesh* mesh = meshComp->GetMesh();
		Shader* shader = meshComp->GetShader();

		std::vector<GLfloat>& vertexData = mesh->GetVertices();
		BindAttributeDataToComponent(Position, vertexData, meshComp, mesh, shader);

		std::vector<GLfloat>& texcoordData = mesh->GetUVs();
		BindAttributeDataToComponent(Texcoord, texcoordData, meshComp, mesh, shader);

		std::vector<GLfloat>& colorData = mesh->GetVertices();
		BindAttributeDataToComponent(Color, colorData, meshComp, mesh, shader);

		std::vector<GLfloat>& normalsData = mesh->GetVertices();
		BindAttributeDataToComponent(Position, normalsData, meshComp, mesh, shader);
	}
}

MeshComponent* MeshComponentManager::AddMeshComponent(Entity* parentEntity, const char* meshName, Shader* meshShader)
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

	m_meshComponents.push_back(MeshComponent(mesh, meshShader));

	MeshComponent& meshComp = m_meshComponents.back();

	meshComp.CreateVertexBuffers();
	BindVertexAttributes(&meshComp);
    AddMeshToBatch(meshComp);
	
	return &meshComp;
}

// This is slow, improve later
int MeshComponentManager::RequestMeshComponent(const char* meshName)
{
	for (int i = 0; i < m_meshComponents.size(); ++i)
	{
		if (m_meshComponents[i].GetMesh()->GetName() == meshName)
		{
			// This is bad, as this pointer will be invalid as soon as the vector resizes
			return i;
		}
	}

	return -1;
}

MeshComponent* MeshComponentManager::RequestMeshComponentByIndex(int index)
{
	if (index >= m_meshComponents.size())
	{
		return nullptr;
	}

	return &(m_meshComponents[index]);
}

void MeshComponentManager::AddMeshToBatch(MeshComponent& meshComp)
{
    // This would be the point I actually added it to the correct batch, but for now just stuffing it into opaque
    AddOpaqueMesh(meshComp);
}

void MeshComponentManager::AddOpaqueMesh(MeshComponent& newMeshComp)
{
    // If a mesh is dynamic or it has transparency then it gets its own batch
    if(!newMeshComp.IsStatic() || newMeshComp.HasTransparency())
    {
        m_opaqueBatches.push_back(Batch(&newMeshComp));
        return;
    }
    
	for (int i = 0; i < m_opaqueBatches.size(); ++i)
	{
		if (m_opaqueBatches[i].IsBatchCompatible(/*newMeshComp.GetShaderId()*/ -1, newMeshComp.GetTextureIds()))
		{
			m_opaqueBatches[i].AddMesh(&newMeshComp);
			return;
		}
	}

	m_opaqueBatches.push_back(Batch(&newMeshComp));
	return;
}

void MeshComponentManager::AddTransparentMesh(MeshComponent& newMeshComp)
{
    
}
