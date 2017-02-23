#ifndef RENDER_SYSTEM_SHARDLITE
#define RENDER_SYSTEM_SHARDLITE

#include <vector>

#ifdef __WINDOWS__
#include <glew.h>
#include <gl\GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

class MeshComponent;

class Batch
{
public:
	Batch(MeshComponent* initialMeshComp);

	bool IsBatchCompatible(int shaderId, std::vector<int> textureIds);

	bool IsMeshInBatch(MeshComponent* mesh);
	bool AddMesh(MeshComponent* newMesh);

	bool UpdateMesh(int meshId);

	void GenerateBatchData();

	inline std::vector<GLfloat> GetVertexData() { return m_vertexInfo; }

private:
	int m_shaderId;
	std::vector<int> m_textureIds;

	std::vector<int> m_batchMeshIds;

	std::vector<GLfloat> m_vertexInfo;
};

#endif
