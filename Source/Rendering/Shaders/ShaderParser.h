#ifndef SHADER_PARSER_CACHE
#define SHADER_PARSER_CACHE

#include "../GLIncludes.h"

#include <string>

class VertexAttribute;
class ShaderUniform;

class ShaderParser
{
public:
	void ParseVertexAttributes(GLenum shaderType, const std::string& shaderSource, VertexAttribute* out_attributeArray);
	void ParseShaderUniforms(GLuint shaderProgram, GLenum shaderType, const std::string& shaderSource, ShaderUniform* out_uniformArray);
};

#endif