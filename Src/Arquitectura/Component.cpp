#include "Component.h"
#include "ResourceManager.h"

Component::Component() : active_(true), entity_(nullptr)
{
}


void Component::releaseEntity()
{
	delete entity_;  
	entity_ = nullptr;
}

Component::~Component()
{
}
