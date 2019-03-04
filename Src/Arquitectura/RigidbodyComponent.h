#pragma once
#include "Component.h""
#include <SDL.h>
#include <iostream>
#include "physicSystem.h"


class RigidbodyComponent : public Component
{
public:
	RigidbodyComponent();
	~RigidbodyComponent();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual void handleEvent() {};

protected:

};

