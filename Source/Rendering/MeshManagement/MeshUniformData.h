#ifndef MESH_UNIFORM_DATA
#define MESH_UNIFORM_DATA

#include "../Shaders/ShaderUniform.h"
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

struct MeshUniformData
{
public:
	MeshUniformData()
	{
		m_uniformType = UniformTypeInvalid;

		m_floatUniformVal = 0.f;
		m_intUniformVal = 0;
		m_mat4UniformVal = glm::mat4(1);
	}

	~MeshUniformData() {}

	void BindUniformData(GLuint uniformLoc)
	{
		if (m_uniformType == UniformTypeInvalid)
		{
			return;
		}

		switch (m_uniformVariableType)
		{
			case FloatingPoint:
				glUniform1f(uniformLoc, m_floatUniformVal);
				break;

			case Integer:
				glUniform1i(uniformLoc, m_intUniformVal);
				break;

			case Matrix4f:
				glUniformMatrix4fv(uniformLoc, 1, false, glm::value_ptr(m_mat4UniformVal));
				//glUniformMatrix4fv(uniform.m_uniformLocation, count, uniform.m_transpose, glm::value_ptr(uniformData));
				break;
		}
	}

public:
	// These two should be coupled. As the uniform type implies what the variable type MUST be
	UniformType m_uniformType;
	UniformVariableType m_uniformVariableType;

	float m_floatUniformVal;
	int m_intUniformVal;
	glm::mat4 m_mat4UniformVal;
};

#endif