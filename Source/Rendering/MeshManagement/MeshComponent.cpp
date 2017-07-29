#include "MeshComponent.h"

#include <iostream>

namespace
{
	GLuint CreateVertexArray()
	{
		GLuint vao = 0;
#ifdef _WIN32
		glCreateVertexArrays(1, &vao);
#endif

#ifdef __APPLE__
		glGenVertexArrays(1, &vao);
#endif

		return vao;
	}

	GLuint CreateVertexBuffer()
	{
		GLuint vbo;

		// Just add this in defines until I hide it away in classes properly
#ifdef _WIN32
		glCreateBuffers(1, &vbo);
#endif

#ifdef __APPLE__
		glGenBuffers(1, &vbd);
#endif

		return vbo;
	}

	void BindVertexAttribute(GLuint vaoId, GLuint vboId, GLuint bindingIndex, GLuint size, const GLchar* attributeName, GLuint shaderProgram, const std::vector<GLfloat>& vertexInfo)
	{
		GLuint attribId = glGetAttribLocation(shaderProgram, attributeName);

		if (attribId == -1)
		{
			std::cout << "Binding vertex attribute with name " + std::string(attributeName) + " failed." << std::endl;
		}

#ifdef _WIN32
		glNamedBufferStorage(vboId, vertexInfo.size() * sizeof(GLfloat), &vertexInfo[0], 0);

		glVertexArrayAttribFormat(vaoId, attribId, size, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vaoId, attribId, bindingIndex);
		glEnableVertexAttribArray(attribId);

		glVertexArrayVertexBuffer(vaoId, bindingIndex, vboId, 0, size * sizeof(GLfloat));
#endif

#ifdef __APPLE__
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexInfo.size(), &(vertexInfo[0]), GL_STATIC_DRAW);

		glEnableVertexAttribArray(attribId);
		glVertexAttribPointer(attribId, size, GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), 0);
#endif
	}
}

MeshComponent::MeshComponent(Mesh* mesh, Shader* shader) :
m_mesh(mesh),
m_shader(shader)
{

}

void MeshComponent::CreateVertexBuffers()
{
	m_vao = CreateVertexArray();
	glBindVertexArray(m_vao);

	VertexAttribute* vertexAttributes = m_shader->m_vertexAttributes;

	// Centralise this attribute array length value
	for (int i = 0; i < AllowedAttributeArraySize; ++i)
	{
		if (vertexAttributes[i].m_isValidAttribute)
		{
			m_vertexAttributeVBOs[i] = CreateVertexBuffer();
		}
	}
}

void MeshComponent::BindVertexData(AttributeType attributeType, VertexAttribute& vertexAttribute, const std::vector<GLfloat>& attributeData)
{
	BindVertexAttribute(m_vao, m_vertexAttributeVBOs[attributeType], vertexAttribute.m_bindingIndex,
		vertexAttribute.m_size, vertexAttribute.m_name.c_str(), m_shader->m_shaderProgram, attributeData);
}

void MeshComponent::BindUniformData(UniformVariableType uniformType, ShaderUniform& uniform, float uniformData)
{
	glUniform1f(uniform.m_uniformLocation, uniformData);
}

void MeshComponent::BindUniformData(UniformVariableType uniformType, ShaderUniform& uniform, double uniformData)
{
	glUniform1d(uniform.m_uniformLocation, uniformData);
}

void MeshComponent::BindUniformData(UniformVariableType uniformType, ShaderUniform& uniform, int uniformData)
{
	glUniform1i(uniform.m_uniformLocation, uniformData);
}

void MeshComponent::BindUniformData(UniformVariableType uniformType, ShaderUniform& uniform, glm::mat4 uniformData)
{
	glUniformMatrix4fv(uniform.m_uniformLocation, uniform.m_count, uniform.m_transpose, glm::value_ptr(uniformData));
}