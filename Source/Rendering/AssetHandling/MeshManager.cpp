#include "MeshManager.h"
#include "FbxLoader.h"

#include <string>
#include <iostream>

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

MeshManager::MeshManager()
{

}

MeshManager::~MeshManager()
{

}

Mesh* MeshManager::LoadMesh(const char* meshName)
{
	if (hasEnding(meshName, ".fbx"))
	{
		Mesh* theMesh = FbxLoader::LoadFbx((MeshAssetLocation + meshName).c_str());
		return theMesh;
	}
	else
	{
		std::cout << "Entered file format not recognised." << std::endl;
	}
}

Mesh* MeshManager::GetMesh(const char* meshName)
{
	std::cout << "GetMesh is not yet implemented" << std::endl;
	return nullptr;
}