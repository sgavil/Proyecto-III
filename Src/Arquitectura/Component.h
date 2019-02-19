#pragma once
#include <Ogre.h>

class Component
{
public:
	Component();
	virtual void render(unsigned int time);
	virtual void update(unsigned int time);
	virtual void handleEvent();

	bool isActive() { return active_; };
	void setActive(bool b) { active_ = b; };
	virtual ~Component();
private:
	bool active_;
};

