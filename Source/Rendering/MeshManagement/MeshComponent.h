#ifndef MESH_COMPONENT_SHARDLITE
#define MESH_COMPONENT_SHARDLITE

#include "../../EntityComponent/Component.h"

// Extract Shader from ShaderCache
#include "../Shaders/ShaderCache.h"

// Extract AttributeType from ShaderParser
#include "../Shaders/ShaderParser.h"

#include <vector>

class Mesh;

class MeshComponent : public Component
{
public:
	MeshComponent(Mesh* mesh, Shader* shader);

	bool IsTransparent() {return m_isTransparent;}

	inline Shader* GetShader() { return m_shader; }
	inline std::vector<int> GetTextureIds() { return m_textureIds; }

	inline Mesh* GetMesh() { return m_mesh; }
    
    inline bool IsStatic() {return m_static;}
    inline bool HasTransparency() {return m_hasTransparency;}

	void CreateVertexBuffers();
	void BindVertexData(AttributeType attributeType, VertexAttribute& vertexAttribute, const std::vector<GLfloat>& attributeData);

private:
	Mesh* m_mesh;

    bool m_static;
    bool m_hasTransparency;
    
	Shader* m_shader;
	std::vector<int> m_textureIds;

	bool m_isTransparent;

	GLuint m_vao;
	GLuint m_vertexAttributeVBOs[AllowedAttributeArraySize] {0};
};

#endif
