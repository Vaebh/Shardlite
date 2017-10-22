#include "MeshComponent.h"

#include "../Shaders/Shader.h"
#include "Mesh.h"
#include "../../EntityComponent/Entity.h"

#include "../GLVertexUtility.hpp"

#include <iostream>

MeshComponent::MeshComponent(Mesh* mesh, Shader* shader, Entity* parentEntity) :
m_mesh(mesh),
m_shader(shader)
{
	m_parentEntity = parentEntity;
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

void MeshComponent::BindUniformData(UniformType uniformType, float uniformData)
{
	ShaderUniform& uniform = m_shader->m_shaderUniforms[uniformType];
	if (uniform.m_isValidUniform)
	{
		return;
	}

	glUniform1f(uniform.m_uniformLocation, uniformData);
}

void MeshComponent::BindUniformData(UniformType uniformType, double uniformData)
{
	ShaderUniform& uniform = m_shader->m_shaderUniforms[uniformType];
	if (uniform.m_isValidUniform)
	{
		return;
	}

	glUniform1d(uniform.m_uniformLocation, uniformData);
}

void MeshComponent::BindUniformData(UniformType uniformType, int uniformData)
{
	ShaderUniform& uniform = m_shader->m_shaderUniforms[uniformType];
	if (uniform.m_isValidUniform)
	{
		return;
	}

	glUniform1i(uniform.m_uniformLocation, uniformData);
}

void MeshComponent::BindUniformData(UniformType uniformType, glm::mat4 uniformData, GLint count)
{
	ShaderUniform& uniform = m_shader->m_shaderUniforms[uniformType];
	if (uniform.m_isValidUniform)
	{
		return;
	}

	glUniformMatrix4fv(uniform.m_uniformLocation, count, uniform.m_transpose, glm::value_ptr(uniformData));
}

DrawCallObject MeshComponent::MakeDrawCallObject()
{
	// need this to be the z from the camera
	return DrawCallObject(this, m_parentEntity->_position.z, m_vao, GetVertexCount());
}

void MeshComponent::ShutDown()
{
	glDeleteVertexArrays(1, &m_vao);
	for (int i = 0; i < AllowedAttributeArraySize; ++i)
	{
		if (m_vertexAttributeVBOs[i] != 0)
		{
			glDeleteBuffers(1, &(m_vertexAttributeVBOs[i]));
		}
	}
}