#include "Mesh.h"

#include "../Animation/Skeleton.h"

int Mesh::CurrentMeshId = 0;

Mesh::Mesh(std::vector<GLfloat> verts, const char* name) :
m_vertices(verts),
m_name(name)
{
	m_meshId = CurrentMeshId++;
}

Mesh::~Mesh()
{

}

int Mesh::GetTriangleCount()
{
	if (m_vertices.size() == 0)
	{
		return 0;
	}

	return m_vertices.size() / 3;
}

std::vector<glm::mat4> Mesh::GetJointTransforms()
{
	// iterate over skeleton and put all joint matrices into a single vector

	std::vector<glm::mat4> jointMatrices;
	jointMatrices.reserve(m_skeleton->_joints.size());

	for (int i = 0; i < m_skeleton->_joints.size(); ++i)
	{
		jointMatrices.push_back(m_skeleton->_joints[i]._globalBindPoseInverse);
	}

	return jointMatrices;
}