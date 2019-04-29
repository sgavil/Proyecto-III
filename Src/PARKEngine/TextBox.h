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

	virtual void save(json file) {};

	void setText(std::string s);

private:
	std::string text;

};

REGISTER_TYPE(TextBox)