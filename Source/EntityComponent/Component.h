#ifndef COMPONENT_SHARDLITE
#define COMPONENT_SHARDLITE

class Entity;

class Component
{
public:
    friend class Entity;
	Component();
	virtual ~Component();

	void Update();

	inline int GetComponentId() { return m_componentId; }

protected:
	int m_componentId;
	static int CurrentComponentId;
    
    Entity* m_parentEntity;
};

#endif
