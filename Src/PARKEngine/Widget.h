#pragma once
#include "Component.h"
#include "HUDManager.h"

using namespace std;

class Widget : public Component
{
protected:

	CEGUI::Window* window;
	std::string type;

public:
	Widget();
	~Widget();

	virtual void load(json file);

	//Métodos principales
	virtual void render(unsigned int time) {}
	virtual void update(unsigned int time) {}
	virtual bool handleEvent(unsigned int time);

	virtual void receive(Message* msg) {};

	void setText(std::string s);
	void setFont(std::string s);
};

REGISTER_TYPE(Widget)