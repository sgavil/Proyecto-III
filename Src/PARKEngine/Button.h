#pragma once
#include "Component.h"
#include "HUDManager.h"

class Button : public Component
{
private:
	std::string windowState;
	std::string nextState;

public:
	Button();
	~Button();

	void load(json file);

	//Métodos principales
	virtual void render(unsigned int time) {}
	virtual void update(unsigned int time) {}
	virtual bool handleEvent(unsigned int time);

	bool onClick(const CEGUI::EventArgs& e);

	virtual void receive(Message* msg) {};
};

REGISTER_TYPE(Button)