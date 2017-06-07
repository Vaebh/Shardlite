#include "Skeleton.h"

#include <glm.hpp>

Joint::Joint(std::string name, int parentIndex) :
	_name(name),
	_parentIndex(parentIndex),
	_animationKeyframe(nullptr)
{
	_globalBindPoseInverse = glm::mat4(1);
}

Joint::~Joint()
{
	while (_animationKeyframe)
	{
		Keyframe* temp = _animationKeyframe->_next;
		delete _animationKeyframe;
		_animationKeyframe = temp;
	}
}

void Skeleton::GetJointTransforms(std::vector<glm::mat4>& jointVec)
{
	for (int i = 0; i < _joints.size(); ++i)
	{
		jointVec.push_back(_joints[i]._globalBindPoseInverse);
	}
}