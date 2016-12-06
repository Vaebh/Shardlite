#include "Entity.h"
#include "Component.h"
#include <algorithm>
#include <assert.h>

namespace
{
	long ENTITY_ID = 0;
}

Entity::Entity()
{
	_id = ++ENTITY_ID;
}

Entity::~Entity()
{
	_id = -1;
}

Component* Entity::RemoveComponent(Component* comp)
{
	auto foundIter = std::find(_componentVec.begin(), _componentVec.end(), comp);
	if (foundIter == _componentVec.end())
	{
		// TODO - Print out log when I have logs
		return nullptr;
	}
	else
	{
		Component* oldComp = *foundIter;
		_componentVec.erase(foundIter);
		return oldComp;
	}
}

void Entity::Update()
{
	for (int i = 0; i < _componentVec.size(); ++i)
	{
		if (_componentVec[i] == nullptr)
		{
			// TODO - Mark component for deletion
			continue;
		}

		_componentVec[i]->Update();
	}
}