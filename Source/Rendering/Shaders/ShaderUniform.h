#ifndef SHADER_UNIFORM_SHARDLITE
#define SHADER_UNIFORM_SHARDLITE

#include "../GLIncludes.h"

#include <string>

const int AllowedUniformArraySize = 3;

enum UniformVariableType
{
	FloatingPoint,
	Double,
	Integer,
	Matrix4f
};

enum UniformType
{
	Model = 0,
	View = 1,
	Projection = 2
};

struct ShaderUniform
{
	std::string m_name;
	UniformVariableType m_variableType;
	GLint m_uniformLocation;
	GLsizei m_count;
	GLboolean m_transpose;

	bool m_isValidUniform;

	ShaderUniform() {}

	ShaderUniform(std::string name, UniformVariableType variableType, GLint uniformLocation, GLsizei count) :
		m_name(name),
		m_variableType(variableType),
		m_uniformLocation(uniformLocation),
		m_count(count),
		m_transpose(GL_FALSE),
		m_isValidUniform(false)
	{}
};

#endif