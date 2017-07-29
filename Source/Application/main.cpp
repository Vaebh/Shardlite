#include "Application.h"

#include "assimp\Importer.hpp"
#include "assimp\postprocess.h"

#include <iostream>
#include <math.h>

#undef main

int main()
{
	Application app;
	app.StartUpSystems();

	while(true)
	{
		if (app.Update())
		{
			app.ShutDownSystems();
			return 0;
		}
	}

	return 0;
}

void AssimpTest()
{
	Assimp::Importer Importer;
	const aiScene* pScene = Importer.ReadFile("Assets/Models/skeleton.fbx", aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (pScene) {
		std::cout << "loaded" << std::endl;
	}
	else {
		std::cout << "error" << std::endl;
	}
}

// Old animation code

/*std::vector<glm::mat4> jointTransforms;
meshComp->GetMesh()->m_skeleton->GetJointTransforms(jointTransforms);

for (int i = 0; i < meshComp->GetMesh()->m_skeleton->_joints.size(); ++i)
{
//meshComp->GetMesh()->m_skeleton->_joints[i]._node->index
}

uniformLoc = glGetUniformLocation(shaderProgram, "jointTransforms");
glUniformMatrix4fv(uniformLoc, jointTransforms.size(), GL_FALSE, glm::value_ptr(jointTransforms[0]));*/