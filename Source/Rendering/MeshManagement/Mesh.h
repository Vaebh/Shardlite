#ifndef MESH_SHARDLITE
#define MESH_SHARDLITE

#include "../GLIncludes.h"

#include <vector>
#include <string>
#include <glm.hpp>

class Skeleton;

class Mesh
{
public:
	explicit Mesh(std::vector<GLfloat> verts, const char* name);
	~Mesh();

	inline std::vector<GLfloat>& GetVertices() { return m_vertices; }
	inline void SetVertices(std::vector<GLfloat> newVerts) { m_vertices = newVerts; }

	inline std::vector<GLfloat>& GetUVs() { return m_uvs; }
	inline void SetUVs(std::vector<GLfloat> newUVs) { m_uvs = newUVs; }

	inline std::vector<GLint>& GetJointIndices() { return m_jointIndices; }
	inline void SetJointIndices(std::vector<GLint> newJointIndices) { m_jointIndices = newJointIndices; }

	inline std::vector<GLfloat>& GetJointWeights() { return m_jointWeights; }
	inline void SetJointWeights(std::vector<GLfloat> newJointWeights) { m_jointWeights = newJointWeights; }

	std::vector<glm::mat4> GetJointTransforms();

	inline int GetVertexCount() { return m_vertices.size(); }
	int GetTriangleCount();

	inline std::string GetName() { return m_name; }
	inline int GetMeshId() { return m_meshId; }

	float m_depthValue;

	Skeleton* m_skeleton;

	std::vector<GLint> m_jointIndices;
	std::vector<GLfloat> m_jointWeights;

private:
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_uvs;

	std::string m_name;

	int m_meshId;
	static int CurrentMeshId;
};

#endif
