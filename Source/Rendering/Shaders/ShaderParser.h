#ifndef SHADER_PARSER_CACHE
#define SHADER_PARSER_CACHE

#include "VertexAttribute.h"

#include "../GLIncludes.h"

class ShaderParser
{
public:
	void ParseVertexAttributes(GLenum shaderType, const std::string& shaderSource, VertexAttribute* out_attributeArray);
};

#endif