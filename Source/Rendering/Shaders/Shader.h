#ifndef SHADER_SHARDLITE
#define SHADER_SHARDLITE

#include "VertexAttribute.h"

#include "../GLIncludes.h"

struct Shader
{
	int m_id;
	GLuint m_shaderProgram;

	VertexAttribute m_vertexAttributes[AllowedAttributeArraySize];
};

#endif