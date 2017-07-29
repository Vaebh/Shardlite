#ifndef VERTEX_ATTRIBUTE_SHARDLITE
#define VERTEX_ATTRIBUTE_SHARDLITE

#include <string>

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

#endif