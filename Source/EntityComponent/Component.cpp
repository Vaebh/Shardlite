#include "Component.h"
#include <iostream>

int Component::CurrentComponentId = 0;

Component::Component()
{
	m_componentId = CurrentComponentId++;
}

Component::~Component()
{
}

void Component::Update()
{
	std::cout << "Component updating" << std::endl;
}