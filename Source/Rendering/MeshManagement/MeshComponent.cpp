#include "MeshComponent.h"
#include "Mesh.h"

#include "../GLVertexUtility.hpp"
#include "../Shaders/Shader.h"

#include "../../EntityComponent/Entity.h"

#include <iostream>

MeshComponent::MeshComponent(Mesh* mesh, Shader* shader, Entity* parentEntity) :
m_mesh(mesh),
m_shader(shader)
{
	m_parentEntity = parentEntity;

	for (int i = 0; i < NumUniforms; ++i)
	{
		m_meshUniformData[i] = MeshUniformData();
	}
}

void MeshComponent::CreateVertexBuffers()
{
	m_vao = CreateVertexArray();
	glBindVertexArray(m_vao);

	VertexAttribute* vertexAttributes = m_shader->m_vertexAttributes;

	for (int i = 0; i < AllowedAttributeArraySize; ++i)
	{
		if (vertexAttributes[i].m_isValidAttribute)
		{
			m_vertexAttributeVBOs[i] = CreateVertexBuffer();
		}
	}
}

int MeshComponent::GetVertexCount()
{
	return GetMesh()->GetVertexCount();
}

void MeshComponent::BindVertexData(AttributeType attributeType, VertexAttribute& vertexAttribute, const std::vector<GLfloat>& attributeData)
{
	BindVertexAttribute(m_vao, m_vertexAttributeVBOs[attributeType], vertexAttribute.m_bindingIndex,
		vertexAttribute.m_size, vertexAttribute.m_name.c_str(), m_shader->m_shaderProgram, attributeData);
}

void MeshComponent::SetUniformData(UniformType uniformType, float uniformData)
{
	ShaderUniform& uniform = m_shader->m_shaderUniforms[uniformType];
	if (uniform.m_isValidUniform)
	{
		return;
	}

	m_meshUniformData[uniformType].m_uniformType = uniformType;
	m_meshUniformData[uniformType].m_uniformVariableType = FloatingPoint;
	m_meshUniformData[uniformType].m_floatUniformVal = uniformData;
}

void MeshComponent::SetUniformData(UniformType uniformType, int uniformData)
{
	ShaderUniform& uniform = m_shader->m_shaderUniforms[uniformType];
	if (uniform.m_isValidUniform)
	{
		return;
	}

	m_meshUniformData[uniformType].m_uniformType = uniformType;
	m_meshUniformData[uniformType].m_uniformVariableType = Integer;
	m_meshUniformData[uniformType].m_intUniformVal = uniformData;
}

void MeshComponent::SetUniformData(UniformType uniformType, glm::mat4 uniformData, GLint count)
{
	ShaderUniform& uniform = m_shader->m_shaderUniforms[uniformType];
	if (uniform.m_isValidUniform)
	{
		return;
	}

	m_meshUniformData[uniformType].m_uniformType = uniformType;
	m_meshUniformData[uniformType].m_uniformVariableType = Matrix4f;
	m_meshUniformData[uniformType].m_mat4UniformVal = uniformData;
}

void MeshComponent::BindUniformValues()
{
	for (int i = 0; i < NumUniforms; ++i)
	{
		ShaderUniform& uniform = m_shader->m_shaderUniforms[m_meshUniformData[i].m_uniformType];

		m_meshUniformData[i].BindUniformData(uniform.m_uniformLocation);
	}
}

DrawCallObject MeshComponent::MakeDrawCallObject()
{
	// need this to be the z from the camera
	return DrawCallObject(this, m_parentEntity->_position.z, m_vao, GetVertexCount());
}

void MeshComponent::BindVertexArrayObject()
{
	glBindVertexArray(m_vao);
}

void MeshComponent::DeleteGLObjects()
{
	DeleteVertexArrayObject();
	DeleteVertexBufferObjects();
}

void MeshComponent::DeleteVertexArrayObject()
{
	glDeleteVertexArrays(1, &m_vao);
}

void MeshComponent::DeleteVertexBufferObjects()
{
	for (int i = 0; i < AllowedAttributeArraySize; ++i)
	{
		if (m_vertexAttributeVBOs[i] != 0)
		{
			glDeleteBuffers(1, &(m_vertexAttributeVBOs[i]));
		}
	}
}