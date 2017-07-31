#include "ShaderParser.h"

#include "VertexAttribute.h"
#include "ShaderUniform.h"

#include <vector>
#include <iostream>

namespace
{
	const std::string AllowedAttributes[AllowedAttributeArraySize] =
	{
		"vec3 position",
		"vec2 texcoord",
		"vec3 color",
		"vec3 normals",
		"ivec4 in_jointIndices",
		"vec4 in_jointWeights"
	};

	const std::string AllowedUniforms[AllowedUniformArraySize] =
	{
		"uniform mat4 model",
		"uniform mat4 view",
		"uniform mat4 projection",
		"uniform sampler2D textureSampler"
	};

	bool CreateVertexAttribute(AttributeType attributeType, VertexAttribute* out_attributeArray)
	{
		switch (attributeType)
		{
			case Position:
				out_attributeArray[0] = VertexAttribute("position", 3, 0);
				break;

			case Texcoord:
				out_attributeArray[1] = VertexAttribute("texcoord", 2, 1);
				break;

			case Color:
				out_attributeArray[2] = VertexAttribute("color", 3, 2);
				break;

			case Normals:
				out_attributeArray[3] = VertexAttribute("normals", 3, 3);
				break;

			case JointIndices:
				out_attributeArray[4] = VertexAttribute("in_jointIndices", 4, 4);
				break;

			case JointWeights:
				out_attributeArray[5] = VertexAttribute("in_jointWeights", 4, 5);
				break;
		}

		return true;
	}

	bool CreateShaderUniform(UniformType uniformType, GLint shaderProgram, ShaderUniform* out_uniformArray)
	{
		GLint uniformLoc = -1;

		switch (uniformType)
		{
			case Model:
				uniformLoc = glGetUniformLocation(shaderProgram, "model");
				if (uniformLoc == -1)
				{
					return false;
				}

				out_uniformArray[0] = ShaderUniform("model", Matrix4f, uniformLoc);
				break;

			case View:
				uniformLoc = glGetUniformLocation(shaderProgram, "view");
				if (uniformLoc == -1)
				{
					return false;
				}

				out_uniformArray[1] = ShaderUniform("view", Matrix4f, uniformLoc);
				break;

			case Projection:
				uniformLoc = glGetUniformLocation(shaderProgram, "projection");
				if (uniformLoc == -1)
				{
					return false;
				}

				out_uniformArray[2] = ShaderUniform("projection", Matrix4f, uniformLoc);
				break;

			case JointTransforms:
				uniformLoc = glGetUniformLocation(shaderProgram, "jointTransforms");
				if (uniformLoc == -1)
				{
					return false;
				}

				out_uniformArray[3] = ShaderUniform("jointTransforms", Matrix4fArray, uniformLoc);
				break;

			case TextureSampler:
				uniformLoc = glGetUniformLocation(shaderProgram, "textureSampler");
				if (uniformLoc == -1)
				{
					return false;
				}

				out_uniformArray[4] = ShaderUniform("textureSampler", Integer, uniformLoc);
				break;
		}

		return true;
	}
}

// Improve by putting all attributes inside a block and only searching within that
// Remove print out once this is solid
void ShaderParser::ParseVertexAttributes(GLenum shaderType, const std::string& shaderSource, VertexAttribute* out_attributeArray)
{
	for (int i = 0; i < AllowedAttributeArraySize; ++i)
	{
		std::string::size_type index = shaderSource.find(AllowedAttributes[i]);
		if (index != std::string::npos)
		{
			CreateVertexAttribute((AttributeType)i, out_attributeArray);

			std::cout << std::string("Found vertex attribute: ").c_str() << shaderSource.substr(index, AllowedAttributes[i].size()).c_str() << std::endl;
		}
	}
}

// Improve by putting all attributes inside a block and only searching within that
// Remove print out once this is solid
void ShaderParser::ParseShaderUniforms(GLuint shaderProgram, GLenum shaderType, const std::string& shaderSource, ShaderUniform* out_uniformArray)
{
	for (int i = 0; i < AllowedUniformArraySize; ++i)
	{
		std::string::size_type index = shaderSource.find(AllowedUniforms[i]);
		if (index != std::string::npos)
		{
			if (CreateShaderUniform((UniformType)i, shaderProgram, out_uniformArray))
			{
				std::cout << std::string("Found uniform: ").c_str() << shaderSource.substr(index, AllowedUniforms[i].size()).c_str() << std::endl;
			}
		}
	}
}