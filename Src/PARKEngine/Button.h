#pragma once
#include "Component.h"


class Button : public Component
{
private:

	std::string nextState;

public:
	Button();
	~Button();

	void load(json file);

	//Métodos principales
	virtual void render(unsigned int time) {}
	virtual void update(unsigned int time) {}
	virtual bool handleEvent(unsigned int time);

	virtual void receive(Message* msg) {};
};

REGISTER_TYPE(Button)