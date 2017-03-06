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
    
    inline bool IsStatic() {return m_static;}
    inline bool HasTransparency() {return m_hasTransparency;}

private:
	Mesh* m_mesh;

    bool m_static;
    bool m_hasTransparency;
    
	int m_shaderId;
	std::vector<int> m_textureIds;

	bool m_isTransparent;
};

#endif
