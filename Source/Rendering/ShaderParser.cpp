#include "ShaderParser.h"

#include <vector>
#include <iostream>

namespace
{
	const std::string AllowedAttributes[AllowedAttributeArraySize] =
	{
		"vec3 position",
		"vec2 texcoord",
		"vec3 color",
		"vec3 normals"
	};

	const std::string AllowedUniforms[] =
	{
		"Model",
		"View",
		"Projection"
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
				out_attributeArray[3] = VertexAttribute("normals", 3, 2);
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