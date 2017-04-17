#include "Skeleton.h"

#include <glm.hpp>

Joint::Joint(std::string name, int parentIndex) :
	_name(name),
	_parentIndex(parentIndex)
{
	_localTransform = glm::mat4(1);
}

Joint::~Joint()
{
	
}