#ifndef MESH_COMPONENT_SHARDLITE
#define MESH_COMPONENT_SHARDLITE

#include "../../EntityComponent/Component.h"

#include "../Shaders/VertexAttribute.h"
#include "../Shaders/ShaderUniform.h"

#include "../DrawCallObject.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <vector>

class Mesh;
class Shader;

class MeshComponent : public Component
{
public:
	MeshComponent(Mesh* mesh, Shader* shader, Entity* parentEntity);

	bool IsTransparent() {return m_isTransparent;}

	inline Shader* GetShader() { return m_shader; }
	inline std::vector<int> GetTextureIds() { return m_textureIds; }

	inline Mesh* GetMesh() { return m_mesh; }

	inline GLuint GetVAO() { return m_vao; }
    
    inline bool IsStatic() {return m_static;}
    inline bool HasTransparency() {return m_hasTransparency;}

	void CreateVertexBuffers();
	void BindVertexData(AttributeType attributeType, VertexAttribute& vertexAttribute, const std::vector<GLfloat>& attributeData);

	void BindUniformData(UniformType uniformType, float uniformData);
	void BindUniformData(UniformType uniformType, double uniformData);
	void BindUniformData(UniformType uniformType, int uniformData);
	void BindUniformData(UniformType uniformType, glm::mat4 uniformData, GLint count = 1);

	DrawCallObject MakeDrawCallObject();

	void ShutDown();

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
