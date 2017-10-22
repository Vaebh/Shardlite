#include "MeshComponentManager.h"
#include "../../Systems/SetupUtils.h"

#include "../../EntityComponent/Entity.h"
#include "MeshAssetManager.h"

#include "../Shaders/Shader.h"
#include "../Shaders/VertexAttribute.h"

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

int MeshComponentManager::AddMeshComponent(Entity* parentEntity, const char* meshName, Shader* meshShader)
{
	if (parentEntity == nullptr)
	{
		return -1;
	}

	Mesh* mesh = MeshAssetManager::GetMesh(meshName);
	if (mesh == nullptr)
	{
		mesh = MeshAssetManager::LoadMesh(meshName);

		if (mesh == nullptr)
		{
			return -1;
		}
	}

	m_meshComponents.push_back(MeshComponent(mesh, meshShader, parentEntity));

	MeshComponent& meshComp = m_meshComponents.back();

	meshComp.CreateVertexBuffers();
	BindVertexAttributes(&meshComp);

	glUseProgram(meshShader->m_shaderProgram);
	glm::mat4 proj = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 1000.0f);
	meshComp.BindUniformData(Projection, proj);
	
	return m_meshComponents.size() - 1;
}

// This is slow, improve later
int MeshComponentManager::RequestMeshComponent(const char* meshName)
{
	for (int i = 0; i < m_meshComponents.size(); ++i)
	{
		if (m_meshComponents[i].GetMesh()->GetName() == meshName)
		{
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

int MeshComponentManager::StartUp()
{
	return SETUP_SUCCESS;
}

int MeshComponentManager::ShutDown()
{
	for (int i = 0; i < m_meshComponents.size(); ++i)
	{
		m_meshComponents[i].DeleteGLObjects();
	}

	return SETUP_SUCCESS;
}