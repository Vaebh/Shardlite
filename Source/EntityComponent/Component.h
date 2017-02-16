#ifndef COMPONENT_SHARDLITE
#define COMPONENT_SHARDLITE

class Entity;

class Component
{
public:
	Component();
	~Component();

	void Update();

	inline int GetComponentId() { return m_componentId; }

protected:
	int m_componentId;

	static int CurrentComponentId;
};

#endif