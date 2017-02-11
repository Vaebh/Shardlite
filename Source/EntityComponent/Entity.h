#ifndef ENTITY_SHARDLITE
#define ENTITY_SHARDLITE

#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

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

	glm::vec3 _position;
	glm::quat _rotation;
	glm::vec3 _scale;

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