#include "Component.h"
#include <iostream>

Component::Component()
{
}

Component::~Component()
{
}

void Component::Update()
{
	std::cout << "Component updating" << std::endl;
}