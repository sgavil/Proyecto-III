#pragma once
#include "Widget.h"
#include "HUDManager.h"

using namespace std;

class WindowBox : public Widget
{

public:
	WindowBox();
	~WindowBox();


	void load(json file);
	virtual void start();
	virtual void receive(Message* msg) {};

	virtual void save(json& file) {};


private:
	std::string text;
	vector<string> hijos;

	std::string closeCallback;
	std::string closeCallbackBackParam;

	bool closeWindow(const CEGUI::EventArgs& e);
	bool onClick(const CEGUI::EventArgs & e);
};

REGISTER_TYPE(WindowBox)