#pragma once
#include "Widget.h"
#include "HUDManager.h"

class TextBox : public Widget
{

public:
	TextBox();
	~TextBox();

	void load(json file);

	virtual void receive(Message* msg) {};

	virtual void save(json& file) {};

	void centreText(std::string s);
	void setBackgroundVisible(string boolean);
	void setColorText(string topLeft, string topRight, string botLeft, string botRight);


private:
	std::string text;
};

REGISTER_TYPE(TextBox)