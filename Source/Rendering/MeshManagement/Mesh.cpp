#include "Mesh.h"

int Mesh::CurrentMeshId = 0;

Mesh::Mesh(std::vector<GLfloat> verts) :
m_vertices(verts)
{
	m_meshId = CurrentMeshId++;
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