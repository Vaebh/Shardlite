#ifndef MESH_COMPONENT_SHARDLITE
#define MESH_COMPONENT_SHARDLITE

#include "MeshUniformData.h"

#include "../DrawCallObject.h"

#include "../Shaders/VertexAttribute.h"
#include "../Shaders/ShaderUniform.h"

#include "../../EntityComponent/Component.h"

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include <vector>

class Mesh;
class Shader;

class MeshComponent : public Component
{
public:
	MeshComponent(Mesh* mesh, Shader* shader, Entity* parentEntity);

	inline Shader* GetShader() { return m_shader; }
	inline std::vector<int> GetTextureIds() { return m_textureIds; }

	inline Mesh* GetMesh() { return m_mesh; }
	int GetVertexCount();

	void CreateVertexBuffers();
	void BindVertexArrayObject();

	void BindVertexData(AttributeType attributeType, VertexAttribute& vertexAttribute, const std::vector<GLfloat>& attributeData);

	void SetUniformData(UniformType uniformType, float uniformData);
	void SetUniformData(UniformType uniformType, int uniformData);
	void SetUniformData(UniformType uniformType, glm::mat4 uniformData, GLint count = 1);

	void BindUniformValues();

	DrawCallObject MakeDrawCallObject();

	void DeleteGLObjects();
	void DeleteVertexArrayObject();
	void DeleteVertexBufferObjects();

private:
	Mesh* m_mesh;
    
	Shader* m_shader;
	std::vector<int> m_textureIds;

	GLuint m_vao;
	GLuint m_vertexAttributeVBOs[AllowedAttributeArraySize] {0};

	MeshUniformData m_meshUniformData[NumUniforms];
};

#endif
