#ifndef BATCH_SHARDLITE
#define BATCH_SHARDLITE

#include "../GLIncludes.h"

#include <vector>

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
	inline int GetVertexCount() { return m_vertexInfo.size(); }

private:
	int m_shaderId;
	std::vector<int> m_textureIds;

	std::vector<int> m_batchMeshIds;

	std::vector<GLfloat> m_vertexInfo;
    std::vector<GLfloat> m_uvInfo;
};

#endif
