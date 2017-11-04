#ifndef SHADER_UNIFORM_SHARDLITE
#define SHADER_UNIFORM_SHARDLITE

#include "../GLIncludes.h"

#include <string>

const int AllowedUniformArraySize = 4;

enum UniformVariableType
{
	FloatingPoint,
	Double,
	Integer,
	Matrix4f,
	Matrix4fArray
};

enum UniformType
{
	UniformTypeInvalid = -1,
	Model = 0,
	View = 1,
	Projection = 2,
	JointTransforms = 3,
	TextureSampler = 4,
	NumUniforms = 5
};

struct ShaderUniform
{
	std::string m_name;
	UniformVariableType m_variableType;
	GLint m_uniformLocation;
	GLboolean m_transpose;

	bool m_isValidUniform;

	explicit ShaderUniform() {}

	explicit ShaderUniform(std::string name, UniformVariableType variableType, GLint uniformLocation) :
		m_name(name),
		m_variableType(variableType),
		m_uniformLocation(uniformLocation),
		m_transpose(GL_FALSE),
		m_isValidUniform(false)
	{}
};

#endif