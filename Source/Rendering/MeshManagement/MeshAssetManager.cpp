#include "MeshAssetManager.h"
#include "../AssetLoading/FbxLoader.h"

#include "Mesh.h"

#include <string>
#include <iostream>

MeshAssetManager* MeshAssetManager::Instance = nullptr;

namespace
{
	std::string MeshAssetLocation = "Assets/Models/";

	bool hasEnding(std::string const &fullString, std::string const &ending) {
		if (fullString.length() >= ending.length()) {
			return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
		}
		else {
			return false;
		}
	}
}

MeshAssetManager::MeshAssetManager()
{
	Instance = this;
}

MeshAssetManager::~MeshAssetManager()
{

}

Mesh* MeshAssetManager::LoadMesh(const char* meshName)
{
	if (hasEnding(meshName, ".fbx") || hasEnding(meshName, ".FBX"))
	{
		Mesh* theMesh = FbxLoader::LoadFbx((MeshAssetLocation + meshName).c_str());
		if (theMesh == nullptr)
		{
			return nullptr;
		}

		Instance->m_meshes[theMesh->GetMeshId()] = theMesh;
		return theMesh;
	}
	else
	{
		std::cout << "Entered file format not recognised." << std::endl;
	}
}

Mesh* MeshAssetManager::GetMesh(const char* meshName)
{
	/*for (int i = 0; i < Instance->m_meshes.size(); ++i)
	{
		/*if (Instance->m_meshes[i]->GetName() == meshName)
		{
			return Instance->m_meshes[i];
		}*/
	/*}

	std::cout << "GetMesh has failed to find the mesh with name " << meshName << std::endl;*/
	return nullptr;
}

std::map<int, Mesh*> MeshAssetManager::GetMeshes()
{
	return Instance->m_meshes;
}