//
//
//void BuildLocalTransform(FbxNode* node, Joint& joint)
//{
//	FbxDouble3 fbxTrans = node->LclTranslation.Get();
//	glm::vec3 translation(fbxTrans.mData[0], fbxTrans.mData[1], fbxTrans.mData[2]);
//
//	fbxTrans = node->LclRotation.Get();
//	glm::vec3 rot(fbxTrans.mData[0], fbxTrans.mData[1], fbxTrans.mData[2]);
//
//	fbxTrans = node->LclScaling.Get();
//	glm::vec3 scale(fbxTrans.mData[0], fbxTrans.mData[1], fbxTrans.mData[2]);
//
//	/*joint._globalBindPoseInverse = glm::inverse(glm::translate(joint._globalBindPoseInverse, translation) *
//	glm::rotate(joint._globalBindPoseInverse, rot.z, glm::vec3(0.f, 0.f, 1.f)) *
//	glm::rotate(joint._globalBindPoseInverse, rot.y, glm::vec3(0.f, 1.f, 0.f)) *
//	glm::rotate(joint._globalBindPoseInverse, rot.x, glm::vec3(1.f, 0.f, 0.f)) *
//	glm::scale(joint._globalBindPoseInverse, scale));*/
//}
//
//void PopulateSkeleton(Joint& rootJoint, FbxNode* rootNode, Skeleton* skeleton, int parentIndex)
//{
//	if (rootNode == nullptr)
//	{
//		return;
//	}
//
//	int childCount = rootNode->GetChildCount();
//	if (childCount == 0)
//	{
//		return;
//	}
//
//	skeleton->_joints.reserve(skeleton->_joints.size() + childCount);
//
//	for (int i = 0; i < childCount; ++i)
//	{
//		FbxNode* childNode = rootNode->GetChild(i);
//
//		skeleton->_joints.push_back(Joint(childNode->GetName(), parentIndex));
//
//		Joint& childJoint = skeleton->_joints[skeleton->_joints.size() - 1];
//		childJoint._node = childNode;
//
//		BuildLocalTransform(childNode, childJoint);
//		PopulateSkeleton(childJoint, childNode, skeleton, skeleton->_joints.size() - 1);
//	}
//}
//
//void PrintJointParents(Skeleton& skeleton, Joint& joint)
//{
//	std::cout << "My joint name is " + joint._name << std::endl;
//
//	if (joint._parentIndex != -1)
//	{
//		PrintJointParents(skeleton, skeleton._joints[joint._parentIndex]);
//	}
//}
//
//unsigned int FindJointIndexUsingName(Skeleton* skeleton, std::string name)
//{
//	for (int i = 0; i < skeleton->_joints.size(); ++i)
//	{
//		if (skeleton->_joints[i]._name == name)
//		{
//			return i;
//		}
//	}
//
//	return -1;
//}
//
//void ConfigureMatrices(Skeleton* skeleton)
//{
//	for (int i = 0; i < skeleton->_joints.size(); ++i)
//	{
//		if (skeleton->_joints[i]._parentIndex < 0)
//		{
//			continue;
//		}
//
//		FbxAMatrix localFBX = skeleton->_joints[i]._node->EvaluateLocalTransform(0.f);
//
//		glm::mat4 local(localFBX.Get(0, 0), localFBX.Get(0, 1), localFBX.Get(0, 2), localFBX.Get(0, 3),
//			localFBX.Get(1, 0), localFBX.Get(1, 1), localFBX.Get(1, 2), localFBX.Get(1, 3),
//			localFBX.Get(2, 0), localFBX.Get(2, 1), localFBX.Get(2, 2), localFBX.Get(2, 3),
//			localFBX.Get(3, 0), localFBX.Get(3, 1), localFBX.Get(3, 2), localFBX.Get(3, 3));
//
//		FbxAMatrix parentGlobalFBX = skeleton->_joints[skeleton->_joints[i]._parentIndex]._node->EvaluateGlobalTransform(0.f);
//		glm::mat4 parent(parentGlobalFBX.Get(0, 0), parentGlobalFBX.Get(0, 1), parentGlobalFBX.Get(0, 2), parentGlobalFBX.Get(0, 3),
//			parentGlobalFBX.Get(1, 0), parentGlobalFBX.Get(1, 1), parentGlobalFBX.Get(1, 2), parentGlobalFBX.Get(1, 3),
//			parentGlobalFBX.Get(2, 0), parentGlobalFBX.Get(2, 1), parentGlobalFBX.Get(2, 2), parentGlobalFBX.Get(2, 3),
//			parentGlobalFBX.Get(3, 0), parentGlobalFBX.Get(3, 1), parentGlobalFBX.Get(3, 2), parentGlobalFBX.Get(3, 3));
//
//		skeleton->_joints[i]._globalBindPoseInverse *= local * parent;
//
//		//skeleton->_joints[i]._globalBindPoseInverse *= skeleton->_joints[skeleton->_joints[i]._parentIndex]._globalBindPoseInverse;
//	}
//}
//
//struct JointWeight
//{
//	unsigned int _jointIndex;
//	GLfloat _jointWeight;
//
//	JointWeight(unsigned int jointIndex, GLfloat jointWeight) :
//		_jointIndex(jointIndex),
//		_jointWeight(jointWeight)
//	{}
//};
//
//std::map<unsigned int, std::vector<JointWeight>> ProcessJointAnimationData(FbxScene* scene, Skeleton* skeleton, FbxNode* rootNode, FbxMesh* fbxMesh, Mesh* theMesh)
//{
//	std::map<unsigned int, std::vector<JointWeight>> _weightsMap;
//
//	FbxSkin* currSkin = reinterpret_cast<FbxSkin*>(fbxMesh->GetDeformer(0, FbxDeformer::eSkin));
//	if (!currSkin)
//	{
//		return _weightsMap;
//	}
//
//	unsigned int numOfClusters = currSkin->GetClusterCount();
//	for (unsigned int clusterIndex = 0; clusterIndex < numOfClusters; ++clusterIndex)
//	{
//		FbxCluster* currCluster = currSkin->GetCluster(clusterIndex);
//		std::string currJointName = currCluster->GetLink()->GetName();
//		unsigned int currJointIndex = FindJointIndexUsingName(skeleton, currJointName);
//		FbxAMatrix transformMatrix;
//		FbxAMatrix transformLinkMatrix;
//		FbxAMatrix globalBindposeInverseMatrix;
//
//		currCluster->GetTransformMatrix(transformMatrix);	// The transformation of the mesh at binding time
//		currCluster->GetTransformLinkMatrix(transformLinkMatrix);	// The transformation of the cluster(joint) at binding time from joint space to world space
//		globalBindposeInverseMatrix = transformLinkMatrix.Inverse();// *transformMatrix;
//
//																	/*if (skeleton->_joints[currJointIndex]._parentIndex != -1)
//																	{
//																	globalBindposeInverseMatrix *= skeleton->_joints[currJointIndex]._node->EvaluateLocalTransform(0.5f) *
//																	skeleton->_joints[skeleton->_joints[currJointIndex]._parentIndex]._node->EvaluateGlobalTransform(0.5f);
//																	}*/
//
//		glm::mat4 jointMat(globalBindposeInverseMatrix.Get(0, 0), globalBindposeInverseMatrix.Get(0, 1), globalBindposeInverseMatrix.Get(0, 2), globalBindposeInverseMatrix.Get(0, 3),
//			globalBindposeInverseMatrix.Get(1, 0), globalBindposeInverseMatrix.Get(1, 1), globalBindposeInverseMatrix.Get(1, 2), globalBindposeInverseMatrix.Get(1, 3),
//			globalBindposeInverseMatrix.Get(2, 0), globalBindposeInverseMatrix.Get(2, 1), globalBindposeInverseMatrix.Get(2, 2), globalBindposeInverseMatrix.Get(2, 3),
//			globalBindposeInverseMatrix.Get(3, 0), globalBindposeInverseMatrix.Get(3, 1), globalBindposeInverseMatrix.Get(3, 2), globalBindposeInverseMatrix.Get(3, 3));
//
//		/*glm::mat4 jointMat(globalBindposeInverseMatrix.Get(0, 0), globalBindposeInverseMatrix.Get(1, 0), globalBindposeInverseMatrix.Get(2, 0), globalBindposeInverseMatrix.Get(3, 0),
//		globalBindposeInverseMatrix.Get(0, 1), globalBindposeInverseMatrix.Get(1, 1), globalBindposeInverseMatrix.Get(2, 1), globalBindposeInverseMatrix.Get(3, 1),
//		globalBindposeInverseMatrix.Get(0, 2), globalBindposeInverseMatrix.Get(1, 2), globalBindposeInverseMatrix.Get(2, 2), globalBindposeInverseMatrix.Get(3, 2),
//		globalBindposeInverseMatrix.Get(0, 3), globalBindposeInverseMatrix.Get(1, 3), globalBindposeInverseMatrix.Get(2, 3), globalBindposeInverseMatrix.Get(3, 3));*/
//
//		FbxAMatrix fbxMat;
//		fbxMat.SetIdentity();
//		fbxMat.SetT(FbxVector4(1.0, 1.0, 1.0, 1.0));
//		fbxMat.SetS(FbxVector4(0.1, 0.1, 0.1, 0.1));
//		FbxQuaternion fbxQuat;
//		fbxQuat.SetAxisAngle(FbxVector4(0.f, 0.f, 1.f, 1.f), 90.f);
//		fbxMat.SetQ(fbxQuat);
//
//		/*glm::mat4 jointMat(fbxMat.Get(0, 0), fbxMat.Get(0, 1), fbxMat.Get(0, 2), fbxMat.Get(0, 3),
//		fbxMat.Get(1, 0), fbxMat.Get(1, 1), fbxMat.Get(1, 2), fbxMat.Get(1, 3),
//		fbxMat.Get(2, 0), fbxMat.Get(2, 1), fbxMat.Get(2, 2), fbxMat.Get(2, 3),
//		fbxMat.Get(3, 0), fbxMat.Get(3, 1), fbxMat.Get(3, 2), fbxMat.Get(3, 3));*/
//
//		//skeleton->_joints[currJointIndex]._globalBindPoseInverse = glm::mat4(1);
//		//skeleton._joints[currJointIndex].mNode = currCluster->GetLink();
//		skeleton->_joints[currJointIndex]._globalBindPoseInverse = jointMat;
//
//		// Associate each joint with the control points it affects
//		unsigned int numOfIndices = currCluster->GetControlPointIndicesCount();
//
//		std::vector<GLint> jointIndices;
//		jointIndices.reserve(numOfIndices);
//
//		std::vector<GLfloat> jointWeights;
//		jointWeights.reserve(numOfIndices * 4); // we're using 4 weights per vertex
//
//		for (unsigned int i = 0; i < numOfIndices; ++i)
//		{
//			//jointIndices.push_back(currCluster->GetControlPointIndices()[i]);
//			//jointWeights.push_back(currCluster->GetControlPointWeights()[i]);
//			if (currCluster->GetControlPointIndices()[i] == 14)
//			{
//				std::cout << "Name: " << currCluster->GetName() << " Vertex Index: " << currCluster->GetControlPointIndices()[i] <<
//					" Joint Index: " << currJointIndex <<
//					" Weight: " << currCluster->GetControlPointWeights()[i] << std::endl;
//			}
//
//			JointWeight jointWeight(currJointIndex, currCluster->GetControlPointWeights()[i]);
//
//			_weightsMap[currCluster->GetControlPointIndices()[i]].push_back(jointWeight);
//
//			/*BlendingIndexWeightPair currBlendingIndexWeightPair;
//			currBlendingIndexWeightPair.mBlendingIndex = currJointIndex;
//			currBlendingIndexWeightPair.mBlendingWeight = currCluster->GetControlPointWeights()[i];
//			mControlPoints[currCluster->GetControlPointIndices()[i]]->mBlendingInfo.push_back(currBlendingIndexWeightPair);*/
//		}
//
//		// Get animation information
//		// Now only supports one take
//		FbxAnimStack* currAnimStack = scene->GetSrcObject<FbxAnimStack>(0);
//		FbxString animStackName = currAnimStack->GetName();
//		std::string animName = animStackName.Buffer();
//		FbxTakeInfo* takeInfo = scene->GetTakeInfo(animStackName);
//
//		FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
//		FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
//		FbxLongLong animLength = end.GetFrameCount(FbxTime::eFrames24) - start.GetFrameCount(FbxTime::eFrames24) + 1;
//
//		Keyframe** currAnim = &(skeleton->_joints[currJointIndex]._animationKeyframe);
//
//		for (FbxLongLong i = start.GetFrameCount(FbxTime::eFrames24); i <= end.GetFrameCount(FbxTime::eFrames24); ++i)
//		{
//			FbxTime currTime;
//			currTime.SetFrame(i, FbxTime::eFrames24);
//			*currAnim = new Keyframe();
//			(*currAnim)->_frameNum = i;
//			FbxAMatrix currentTransformOffset = rootNode->EvaluateGlobalTransform(currTime);
//			(*currAnim)->_globalTransform = currentTransformOffset.Inverse() * currCluster->GetLink()->EvaluateGlobalTransform(currTime);
//
//			FbxAMatrix testMat;
//			//testMat = currCluster->GetLink()->EvaluateGlobalTransform(currTime);
//			testMat = currCluster->GetTransformLinkMatrix(testMat);
//
//			if (skeleton->_joints[currJointIndex]._parentIndex != -1)
//			{
//				testMat *= skeleton->_joints[currJointIndex]._node->EvaluateLocalTransform(0.5f) *
//					skeleton->_joints[skeleton->_joints[currJointIndex]._parentIndex]._node->EvaluateGlobalTransform(0.5f);
//			}
//
//			if (i == 0)
//			{
//				glm::mat4 jointMat(testMat.Get(0, 0), testMat.Get(0, 1), testMat.Get(0, 2), testMat.Get(0, 3),
//					testMat.Get(1, 0), testMat.Get(1, 1), testMat.Get(1, 2), testMat.Get(1, 3),
//					testMat.Get(2, 0), testMat.Get(2, 1), testMat.Get(2, 2), testMat.Get(2, 3),
//					testMat.Get(3, 0), testMat.Get(3, 1), testMat.Get(3, 2), testMat.Get(3, 3));
//
//				//skeleton->_joints[currJointIndex]._globalBindPoseInverse = jointMat;
//			}
//
//			currAnim = &((*currAnim)->_next);
//		}
//	}
//
//	std::vector<JointWeight> jointWeightsVec = _weightsMap[14];
//	for (int i = 0; i < jointWeightsVec.size(); ++i)
//	{
//		std::cout << "Joint Index: " << jointWeightsVec[i]._jointIndex << " Joint Weight: " << jointWeightsVec[i]._jointWeight << std::endl;
//	}
//
//	JointWeight defaultWeightPair(0, 0);
//	for (auto itr = _weightsMap.begin(); itr != _weightsMap.end(); ++itr)
//	{
//		for (unsigned int i = itr->second.size(); i <= 4; ++i)
//		{
//			itr->second.push_back(defaultWeightPair);
//		}
//	}
//
//	std::vector<GLint> jointIndices;
//	jointIndices.reserve(_weightsMap.size());
//
//	std::vector<GLfloat> jointWeights;
//	jointWeights.reserve(_weightsMap.size());
//
//	unsigned int bigJointIndex = 0;
//
//	for (unsigned int i = 0; i < _weightsMap.size(); ++i)
//	{
//		for (unsigned int j = 0; j <= 4; ++j)
//		{
//			jointIndices.push_back(_weightsMap[i][j]._jointIndex);
//			jointWeights.push_back(_weightsMap[i][j]._jointWeight);
//			if (bigJointIndex < _weightsMap[i][j]._jointIndex)
//			{
//				bigJointIndex = _weightsMap[i][j]._jointIndex;
//			}
//
//			//std::cout << std::endl << "Joint Index: " << _weightsMap[i][j]._jointIndex << std::endl;
//			//std::cout << "\tWeight " << j << ": " << _weightsMap[i][j]._jointWeight << std::endl;
//		}
//	}
//
//	//theMesh->SetJointIndices(jointIndices);
//	//theMesh->SetJointWeights(jointWeights);
//
//	//std::cout << "biggest joint index: " << bigJointIndex << std::endl;
//
//	/*for (unsigned int i = 0; i < jointIndices.size(); ++i)
//	{
//	std::cout << std::endl << "Joint Index: " << jointIndices[i] << std::endl;
//	}*/
//
//	//for(int i = 0; i < )
//
//	return _weightsMap;
//}
//}