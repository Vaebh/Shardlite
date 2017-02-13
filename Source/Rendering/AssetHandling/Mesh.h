#ifndef MESH_SHARDLITE
#define MESH_SHARDLITE

#include <vector>

#include <glew.h>
#include <gl\GL.h>

class Mesh
{
public:
	Mesh(std::vector<GLfloat> verts);
	~Mesh();

	inline std::vector<GLfloat> GetVertices() { return m_vertices; }
	inline void SetVertices(std::vector<GLfloat> newVerts) { m_vertices = newVerts; }

	inline int GetVertexCount() { return m_vertices.size(); }
	int GetTriangleCount();

private:
	std::vector<GLfloat> m_vertices;
};

#endif