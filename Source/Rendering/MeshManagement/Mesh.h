#ifndef MESH_SHARDLITE
#define MESH_SHARDLITE

#include <vector>

#ifdef __WINDOWS__
#include <glew.h>
#include <gl\GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

#include <string>

class Mesh
{
public:
	Mesh(std::vector<GLfloat> verts);
	~Mesh();

	inline std::vector<GLfloat> GetVertices() { return m_vertices; }
	inline void SetVertices(std::vector<GLfloat> newVerts) { m_vertices = newVerts; }

	inline std::vector<GLfloat> GetUVs() { return m_uvs; }
	inline void SetUVs(std::vector<GLfloat> newUVs) { m_uvs = newUVs; }

	inline int GetVertexCount() { return m_vertices.size(); }
	int GetTriangleCount();

	inline int GetShaderId() { return _shaderId; }

	inline std::string GetName() { return m_name; }
	inline int GetMeshId() { return m_meshId; }

	float m_depthValue;

private:
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_uvs;

	std::string m_name;

	// Index to reference compiled shader
	int _shaderId;

	int m_meshId;
	static int CurrentMeshId;
};

#endif
