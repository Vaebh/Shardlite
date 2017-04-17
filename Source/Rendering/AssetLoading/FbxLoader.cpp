#include "FbxLoader.h"
#include <fbxsdk.h>
#include <iostream>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../MeshManagement/Mesh.h"

#include "../Animation/Skeleton.h"

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

	FbxNode* FindRoot(FbxNode* node)
	{
		if (node->GetNodeAttribute()->GetAttributeType() != FbxNodeAttribute::eSkeleton)
		{
			return nullptr;
		}

		FbxNode* parent = node->GetParent();
		if (parent != nullptr && parent->GetNodeAttribute()->GetAttributeType() != FbxNodeAttribute::eSkeleton)
		{
			return node;
		}

		return FindRoot(node->GetParent());
	}

	void BuildLocalTransform(FbxNode* node, Joint& joint)
	{
		FbxDouble3 fbxTrans = node->LclTranslation.Get();
		glm::vec3 translation(fbxTrans.mData[0], fbxTrans.mData[1], fbxTrans.mData[2]);

		fbxTrans = node->LclRotation.Get();
		glm::vec3 rot(fbxTrans.mData[0], fbxTrans.mData[1], fbxTrans.mData[2]);

		fbxTrans = node->LclScaling.Get();
		glm::vec3 scale(fbxTrans.mData[0], fbxTrans.mData[1], fbxTrans.mData[2]);

		joint._localTransform = glm::inverse(glm::translate(joint._localTransform, translation) *
			glm::rotate(joint._localTransform, rot.z, glm::vec3(0.f, 0.f, 1.f)) *
			glm::rotate(joint._localTransform, rot.y, glm::vec3(0.f, 1.f, 0.f)) *
			glm::rotate(joint._localTransform, rot.x, glm::vec3(1.f, 0.f, 0.f)) *
			glm::scale(joint._localTransform, scale));
	}

	void PopulateSkeleton(Joint& rootJoint, FbxNode* rootNode, Skeleton& skeleton, int parentIndex)
	{
		if (rootNode == nullptr)
		{
			return;
		}

		int childCount = rootNode->GetChildCount();
		if (childCount == 0)
		{
			return;
		}

		skeleton._joints.reserve(skeleton._joints.size() + childCount);

		for (int i = 0; i < childCount; ++i)
		{
			FbxNode* childNode = rootNode->GetChild(i);

			skeleton._joints.push_back(Joint(childNode->GetName(), parentIndex));

			Joint& parentJoint = skeleton._joints[skeleton._joints.size() - 1];
			BuildLocalTransform(childNode, parentJoint);
			PopulateSkeleton(parentJoint, childNode, skeleton, skeleton._joints.size() - 1);
		}
	}
}

void PrintJointParents(Skeleton& skeleton, Joint& joint)
{
	std::cout << "My joint name is " + joint._name << std::endl;

	if (joint._parentIndex != -1)
	{
		PrintJointParents(skeleton, skeleton._joints[joint._parentIndex]);
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

	FbxAxisSystem fbxAxis = scene->GetGlobalSettings().GetAxisSystem();

	if (fbxAxis != FbxAxisSystem::OpenGL)
	{
		std::cout << "fbxaxis not opengl" << std::endl;
	}

	FbxNode* rootNode = scene->GetRootNode();
	FbxMesh* fbxMesh = GetMesh(rootNode);

	std::vector<FbxMesh*> meshes = std::vector<FbxMesh*>();
	GetMeshes(rootNode, meshes);

	if (fbxMesh == nullptr)
	{
		std::cout << "FbxMesh not found" << std::endl;
		return nullptr;
	}

	FbxSkin *pSkin = (FbxSkin*)fbxMesh->GetDeformer(0, FbxDeformer::eSkin);
	if (pSkin == NULL)
		return nullptr;

	// bone count
	int ncBones = pSkin->GetClusterCount();

	if (ncBones > 0)
	{
		// cluster
		FbxCluster* cluster = pSkin->GetCluster(0);

		// bone ref
		FbxNode* pBone = cluster->GetLink();
		FbxNode* root = FindRoot(pBone);

		Skeleton skeleton;
		skeleton._joints.push_back(Joint(root->GetName(), -1));
		PopulateSkeleton(skeleton._joints[0], root, skeleton, 0);

		if (root != nullptr)
		{
			std::cout << "Root name: " << root->GetName() << std::endl;
		}
	}

	bool thing = false;

	// iterate bones
	for (int boneIndex = 0; boneIndex < ncBones; ++boneIndex)
	{
		// cluster
		FbxCluster* cluster = pSkin->GetCluster(boneIndex);

		// bone ref
		FbxNode* pBone = cluster->GetLink();
		if (!thing)
		{
			//thing = true;
			FindRoot(pBone);
		}
		/*if (pBone->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			std::cout << "skellington";
		}*/
		

		// Get the bind pose
		FbxAMatrix bindPoseMatrix, transformMatrix;
		cluster->GetTransformMatrix(transformMatrix);
		cluster->GetTransformLinkMatrix(bindPoseMatrix);

		// decomposed transform components
		FbxVector4 vS = bindPoseMatrix.GetS();
		FbxVector4 vR = bindPoseMatrix.GetR();
		FbxVector4 vT = bindPoseMatrix.GetT();

		int *pVertexIndices = cluster->GetControlPointIndices();
		double *pVertexWeights = cluster->GetControlPointWeights();

		// Iterate through all the vertices, which are affected by the bone
		int ncVertexIndices = cluster->GetControlPointIndicesCount();

		for (int iBoneVertexIndex = 0; iBoneVertexIndex < ncVertexIndices; iBoneVertexIndex++)
		{
			// vertex
			int niVertex = pVertexIndices[iBoneVertexIndex];

			// weight
			float fWeight = (float)pVertexWeights[iBoneVertexIndex];
		}
	}


	std::vector<FbxMesh*> fbxMeshes = std::vector<FbxMesh*>();
	GetMeshes(rootNode, fbxMeshes);
	std::cout << "GetMeshes count is: " << fbxMeshes.size() << std::endl;

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
	std::vector<GLfloat> fbxUVs = std::vector<GLfloat>();//std::vector<GLfloat>(vertexCount * 6);

	FbxStringList UVSetNameList;

	// Get the name of each set of UV coords
	fbxMesh->GetUVSetNames(UVSetNameList);
	FbxArray<FbxVector2> uvtest;
	fbxMesh->GetPolygonVertexUVs(UVSetNameList.GetStringAt(0), uvtest);
	for (int h = 0; h < uvtest.GetCount(); h++)
	{
		fbxUVs.push_back(uvtest[h].mData[0]);
		fbxUVs.push_back(1 - uvtest[h].mData[1]);
	}

	for (int j = 0; j < triangleCount; ++j)
	{
		int index = 0;
		bool texCoordFound = false;
		FbxVector2 fbxUV(0, 0);

		index = fbxMesh->GetPolygonVertex(j, 0);

		int vertIndex = j * 9;

		vertexInfo[vertIndex] = (GLfloat)fbxVerts[index][0];
		vertexInfo[vertIndex + 1] = (GLfloat)fbxVerts[index][1];
		vertexInfo[vertIndex + 2] = (GLfloat)fbxVerts[index][2];

		FbxVector2 fbxTexCoord;
		FbxStringList UVSetNameList;

		// Get the name of each set of UV coords
		fbxMesh->GetUVSetNames(UVSetNameList);

		// Get the UV coords for this vertex in this poly which belong to the first UV set
		// Note: Using 0 as index into UV set list as this example supports only one UV set
		int uvVectorIndex = j * 6;

		/*bool unmapped;
		if (fbxMesh->GetPolygonVertexUV(j, 0, UVSetNameList.GetStringAt(0), fbxTexCoord, unmapped))
		{
			// Convert to floats
			float UVCoord[2];
			fbxUVs[uvVectorIndex] = 1.f - static_cast<GLfloat>(fbxTexCoord[0]);
			fbxUVs[uvVectorIndex + 1] = 1.f - static_cast<GLfloat>(fbxTexCoord[1]);
		}

		fbxTexCoord = FbxVector2();
		if (fbxMesh->GetPolygonVertexUV(j, 1, UVSetNameList.GetStringAt(0), fbxTexCoord, unmapped))
		{
			// Convert to floats
			fbxUVs[uvVectorIndex + 2] = 1.f - static_cast<GLfloat>(fbxTexCoord[0]);
			fbxUVs[uvVectorIndex + 3] = 1.f - static_cast<GLfloat>(fbxTexCoord[1]);
		}

		fbxTexCoord = FbxVector2();
		if (fbxMesh->GetPolygonVertexUV(j, 2, UVSetNameList.GetStringAt(0), fbxTexCoord, unmapped))
		{
			// Convert to floats
			fbxUVs[uvVectorIndex + 4] = 1.f - static_cast<GLfloat>(fbxTexCoord[0]);
			fbxUVs[uvVectorIndex + 5] = 1.f - static_cast<GLfloat>(fbxTexCoord[1]);
		}*/



		//FbxLayerElementUV* layerUVs = fbxMesh->GetLayer(0)->GetUVs();

		//int uvIndex = 0;
		//FbxLayerElement::EReferenceMode referenceMode = layerUVs->GetReferenceMode();
		//FbxLayerElement::EMappingMode mappingMode = layerUVs->GetMappingMode();

		//if (FbxLayerElement::eByPolygonVertex == mappingMode)
		//{
		//	int uvVectorIndex = j * 6;

		//	int id = fbxMesh->GetTextureUVIndex(j, 0);
		//	if (FbxLayerElement::eDirect == referenceMode ||
		//		FbxLayerElement::eIndexToDirect == referenceMode)
		//		uvIndex = id;
		//	//FbxVector2 uv = layerUVs->GetDirectArray()[uvIndex];
		//	FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
		//	fbxMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);
		//	fbxsdk::FbxVector2 uv = uvVertices->GetAt(uvIndex);

		//	fbxUVs[uvVectorIndex] = uv[0];
		//	fbxUVs[uvVectorIndex+1] = uv[1];

		//	id = fbxMesh->GetTextureUVIndex(j, 1);
		//	if (FbxLayerElement::eDirect == referenceMode ||
		//		FbxLayerElement::eIndexToDirect == referenceMode)
		//		uvIndex = id;
		//	//uv = layerUVs->GetDirectArray()[uvIndex];
		//	uvVertices = 0;
		//	fbxMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);
		//	uv = uvVertices->GetAt(uvIndex);

		//	fbxUVs[uvVectorIndex+2] = uv[0];
		//	fbxUVs[uvVectorIndex+3] = uv[1];

		//	id = fbxMesh->GetTextureUVIndex(j, 2);
		//	if (FbxLayerElement::eDirect == referenceMode ||
		//		FbxLayerElement::eIndexToDirect == referenceMode)
		//		uvIndex = id;
		//	//uv = layerUVs->GetDirectArray()[uvIndex];
		//	uvVertices = 0;
		//	fbxMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);
		//	uv = uvVertices->GetAt(uvIndex);

		//	fbxUVs[uvVectorIndex + 4] = uv[0];
		//	fbxUVs[uvVectorIndex + 5] = uv[1];
		//}

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
        std::string nodeName = (std::string)p.GetName();

		std::cout << "found property: " << nodeName.c_str() << std::endl;

		FbxDouble3 colour = p.Get<FbxDouble3>();
		std::cout << colour.mData[0];
	}

	Mesh* shardliteMesh = new Mesh(vertexInfo);
	shardliteMesh->SetUVs(fbxUVs);
	return shardliteMesh;
}
