#ifndef SHADER_PARSER_CACHE
#define SHADER_PARSER_CACHE

#include <string>

#ifdef _WIN32
#include <glew.h>
#include <gl\GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

const int AllowedAttributeArraySize = 4;

struct VertexAttribute
{
	std::string m_name;
	float m_size = -1;
	float m_bindingIndex = -1;
	bool m_isValidAttribute = false;

	VertexAttribute() {}

	VertexAttribute(std::string name, float size, float bindingIndex) :
		m_name(name),
		m_size(size),
		m_bindingIndex(bindingIndex),
		m_isValidAttribute(true)
	{}
};

enum AttributeType
{
	Position = 0,
	Texcoord = 1,
	Color = 2,
	Normals = 3
};

class ShaderParser
{
public:
	void ParseVertexAttributes(GLenum shaderType, const std::string& shaderSource, VertexAttribute* out_attributeArray);
};

#endif