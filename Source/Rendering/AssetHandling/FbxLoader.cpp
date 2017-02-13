#include "FbxLoader.h"
#include <fbxsdk.h>
#include <iostream>

#include "Mesh.h"

namespace
{
	FbxMesh* GetMesh(FbxNode* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		FbxMesh* mesh = node->GetMesh();
		if (mesh != nullptr && mesh->GetPolygonVertexCount() > 0)
		{
			return mesh;
		}

		for (int i = 0; i < node->GetChildCount(); ++i)
		{
			if (node->GetChild(i) == nullptr)
			{
				continue;
			}

			FbxMesh* mesh = node->GetChild(i)->GetMesh();
			if (mesh == nullptr || mesh->GetPolygonVertexCount() <= 0)
			{
				if (node->GetChild(i)->GetChildCount() == 0)
				{
					return nullptr;
				}
				else
				{
					for (int j = 0; j < node->GetChild(i)->GetChildCount(); ++j)
					{
						mesh = GetMesh(node->GetChild(i)->GetChild(j));
						if (mesh != nullptr && mesh->GetPolygonVertexCount() > 0)
						{
							std::cout << "mesh found at indexes i: " << i << " j: " << j << std::endl;
							return mesh;
						}
					}
				}
			}
			else
			{
				std::cout << "mesh found at index i: " << i << std::endl;
				std::cout << "mesh polygon count: " << mesh->GetPolygonCount() << std::endl;
				return mesh;
			}
		}

		return nullptr;
	}

	FbxMesh* GetMeshes(FbxNode* node, std::vector<FbxMesh*>& meshes)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		FbxMesh* mesh = node->GetMesh();
		if (mesh != nullptr)
		{
			meshes.push_back(mesh);
			mesh = nullptr;
			//return mesh;
		}

		for (int i = 0; i < node->GetChildCount(); ++i)
		{
			if (node->GetChild(i) == nullptr)
			{
				continue;
			}

			FbxMesh* mesh = node->GetChild(i)->GetMesh();
			if (mesh == nullptr || mesh->GetPolygonVertexCount() <= 0)
			{
				if (node->GetChild(i)->GetChildCount() == 0)
				{
					return nullptr;
				}
				else
				{
					for (int j = 0; j < node->GetChild(i)->GetChildCount(); ++j)
					{
						mesh = GetMeshes(node->GetChild(i)->GetChild(j), meshes);
						if (mesh != nullptr && mesh->GetPolygonVertexCount() > 0)
						{
							std::cout << "mesh found at indexes i: " << i << " j: " << j << std::endl;
							meshes.push_back(mesh);
							mesh = nullptr;
							//return mesh;
						}
					}
				}
			}
			else
			{
				std::cout << "mesh found at index i: " << i << std::endl;
				std::cout << "mesh polygon count: " << mesh->GetPolygonCount() << std::endl;
				//return mesh;
				meshes.push_back(mesh);
				mesh = nullptr;
			}
		}

		return nullptr;
	}
}

Mesh* FbxLoader::LoadFbx(const char* fileName)
{
	FbxManager *manager = FbxManager::Create();

	FbxIOSettings *ioSettings = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ioSettings);

	FbxImporter *importer = FbxImporter::Create(manager, "");
	if (!importer->Initialize(fileName, -1, manager->GetIOSettings()))
	{
		std::cout << "Initialize unsuccessful" << std::endl;
	}

	if (importer->IsFBX())
	{
		std::cout << "model is an fbx" << std::endl;

		FBXSDK_printf("Animation Stack Information\n");

		int lAnimStackCount = importer->GetAnimStackCount();

		FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);

		for (int i = 0; i < lAnimStackCount; i++)
		{
			FbxTakeInfo* lTakeInfo = importer->GetTakeInfo(i);

			FBXSDK_printf("    Animation Stack %d\n", i);
			FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
			FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

			// Change the value of the import name if the animation stack should be imported 
			// under a different name.
			FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

			// Set the value of the import state to false if the animation stack should be not
			// be imported. 
			FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
			FBXSDK_printf("\n");
		}
	}

	FbxScene *scene = FbxScene::Create(manager, "tempName");

	if (!importer->Import(scene))
	{
		std::cout << "import unsuccessful" << std::endl;
	}
	importer->Destroy();

	FbxNode* rootNode = scene->GetRootNode();
	FbxMesh* fbxMesh = GetMesh(rootNode);

	std::vector<FbxMesh*> meshes = std::vector<FbxMesh*>();
	GetMeshes(rootNode, meshes);

	if (fbxMesh == nullptr)
	{
		std::cout << "FbxMesh not found" << std::endl;
		return nullptr;
	}

	/*if (fbxMesh != nullptr)
	{*/
	int vertexCount = 0;
	vertexCount = fbxMesh->GetPolygonVertexCount();

	int triangleCount = fbxMesh->GetPolygonVertexCount() / 3;
	int indicesCount = fbxMesh->GetPolygonVertexCount();

	FbxVector4* fbxVerts = new FbxVector4[vertexCount];
	int arrayIndex = 0;
	memcpy(fbxVerts, fbxMesh->GetControlPoints(), vertexCount * sizeof(FbxVector4));
	//}
	float wValue = 1.f;
	std::vector<GLfloat> vertexInfo(vertexCount * 9);
	for (int j = 0; j < triangleCount; ++j)
	{
		int index = 0;
		bool texCoordFound = false;

		index = fbxMesh->GetPolygonVertex(j, 0);

		int vertIndex = j * 9;

		vertexInfo[vertIndex] = (GLfloat)fbxVerts[index][0];
		vertexInfo[vertIndex + 1] = (GLfloat)fbxVerts[index][1];
		vertexInfo[vertIndex + 2] = (GLfloat)fbxVerts[index][2];

		index = fbxMesh->GetPolygonVertex(j, 1);
		vertexInfo[vertIndex + 3] = (GLfloat)fbxVerts[index][0];
		vertexInfo[vertIndex + 4] = (GLfloat)fbxVerts[index][1];
		vertexInfo[vertIndex + 5] = (GLfloat)fbxVerts[index][2];

		index = fbxMesh->GetPolygonVertex(j, 2);
		vertexInfo[vertIndex + 6] = (GLfloat)fbxVerts[index][0];
		vertexInfo[vertIndex + 7] = (GLfloat)fbxVerts[index][1];
		vertexInfo[vertIndex + 8] = (GLfloat)fbxVerts[index][2];
	}

	FbxLayer *layer = fbxMesh->GetLayer(0);
	FbxLayerElementMaterial* pMaterialLayer = layer->GetMaterials();
	int numMatIndices = pMaterialLayer->GetIndexArray().GetCount();

	std::vector<GLfloat> colors = std::vector<GLfloat>(numMatIndices * 9);

	for (int i = 0; i < numMatIndices; i++)
	{
		//int matIndex = array->operator[](i);
		int matIndex = pMaterialLayer->GetIndexArray()[i];

		FbxSurfaceMaterial *smat = fbxMesh->GetNode()->GetMaterial(matIndex);
		if (smat->GetClassId().Is(FbxSurfaceLambert::ClassId))
		{
			FbxSurfaceLambert *lam = (FbxSurfaceLambert*)smat;

			FbxPropertyT<FbxDouble3> p = lam->Diffuse;
			FbxDouble3 info = p.Get();

			for (int j = 0; j < 3; j++)
			{
				colors[i * 9 + j * 3 + 0] = (GLfloat)info[0];
				colors[i * 9 + j * 3 + 1] = (GLfloat)info[1];
				colors[i * 9 + j * 3 + 2] = (GLfloat)info[2];
			}
		}
	}

	FbxProperty p = fbxMesh->FindProperty("color", false);
	if (p.IsValid())
	{
		std::string nodeName = p.GetName();

		std::cout << "found property: " << nodeName.c_str() << std::endl;

		FbxDouble3 colour = p.Get<FbxDouble3>();
		std::cout << colour.mData[0];
	}

	Mesh* shardliteMesh = new Mesh(vertexInfo);
	return shardliteMesh;
}