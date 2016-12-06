#ifndef ENTITY_SHARDLITE
#define ENTITY_SHARDLITE

#include <vector>

class Component;

class Entity
{
public:
	Entity();
	~Entity();

	template <typename T>
	Component* AddComponent();
	Component* RemoveComponent(Component* comp);

	void Update();

private:
	long _id;

	std::vector<Component*> _componentVec;
};

#endif

template <typename T>
Component* Entity::AddComponent()
{
	T* comp = new T();
	_componentVec.push_back(comp);

	return comp;
}