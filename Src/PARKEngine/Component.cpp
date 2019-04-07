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

template <typename T>
bool Component::addParameter(T& parameter, json value)
{
	if (!value.empty())
	{
		parameter = value;
		return true;
	}
	return false;
}

Component::~Component()
{
}
