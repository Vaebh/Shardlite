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
};

class Joint
{
public:
	Joint(std::string name, int parentIndex);
	~Joint();

	std::string _name;
	int _parentIndex;

	glm::mat4 _localTransform;
};

#endif