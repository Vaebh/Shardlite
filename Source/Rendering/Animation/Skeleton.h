#ifndef SKELETON_SHARDLITE
#define SKELETON_SHARDLITE

#include <string>

#include <fbxsdk.h>
#include <glm.hpp>
#include <vector>

class Joint;

struct Skeleton
{
	std::vector<Joint> _joints;

	void GetJointTransforms(std::vector<glm::mat4>& jointVec);
};

struct Keyframe
{
	FbxLongLong _frameNum;
	FbxAMatrix _globalTransform;
	Keyframe* _next;

	Keyframe() :
		_next(nullptr)
	{}
};

class Joint
{
public:
	Joint(std::string name, int parentIndex);
	~Joint();

	std::string _name;
	int _parentIndex;

	glm::mat4 _globalBindPoseInverse;

	Keyframe* _animationKeyframe;

	FbxNode* _node;
};

struct BlendingIndexWeightPair
{
	unsigned int _blendingIndex;
	double _blendingWeight;

	BlendingIndexWeightPair() :
		_blendingIndex(0),
		_blendingWeight(0)
	{}
};

#endif