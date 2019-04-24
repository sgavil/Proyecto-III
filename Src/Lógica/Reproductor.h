#pragma once
#include <PARKEngine/AudioManager.h>
#include <PARKEngine/Component.h>

class Reproductor : public Component, Listener
{
public:
	Reproductor();
	~Reproductor();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time) {};
	virtual bool handleEvent(unsigned int time) { return false; };

	virtual void receive(Message* msg);
};

REGISTER_TYPE(Reproductor);

