#pragma once
#include "Components.h"

class BaseCreator
{
public:
	virtual Component* createComponent() const = 0;
	virtual ~BaseCreator() {}
};

class CameraComponentCreator : public BaseCreator
{
public:
	Component* createComponent() const
	{
		Component* e = new CameraComponent();

		return e;
	}
};

class NPCComponentCreator : public BaseCreator
{
public:
	Component* createComponent() const
	{
		Component* e = new NPCComponent();
		
		return e;
	}
};