#ifndef MESH_COMPONENT_SHARDLITE
#define MESH_COMPONENT_SHARDLITE

#include "../../EntityComponent/Component.h"
#include <vector>

class Mesh;

class MeshComponent : public Component
{
public:
	MeshComponent(Mesh* mesh);

	bool IsTransparent() {return m_isTransparent;}

	inline int GetShaderId() { return m_shaderId; }
	inline std::vector<int> GetTextureIds() { return m_textureIds; }

	inline Mesh* GetMesh() { return m_mesh; }

private:
	Mesh* m_mesh;

	int m_shaderId;
	std::vector<int> m_textureIds;

	bool m_isTransparent;
};

#endif