#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> verts) :
m_vertices(verts)
{

}

Mesh::~Mesh()
{

}

int Mesh::GetTriangleCount()
{
	if (m_vertices.size() == 0)
	{
		return 0;
	}

	return m_vertices.size() / 3;
}