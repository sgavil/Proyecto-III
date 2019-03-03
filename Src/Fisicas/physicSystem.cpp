#include "physicSystem.h"

physicSystem* physicSystem::instance_ = nullptr;


physicSystem::physicSystem()
{
	
}


physicSystem * physicSystem::instance()
{
	if (instance_ == nullptr)
		instance_ = new physicSystem();
	return instance_;
}




physicSystem::~physicSystem()
{
}

