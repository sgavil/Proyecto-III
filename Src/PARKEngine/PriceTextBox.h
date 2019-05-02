#pragma once
#include "TextBox.h"
#include "HUDManager.h"

class PriceTextBox : public TextBox
{

public:
	PriceTextBox();
	~PriceTextBox();

	void load(json file);

	virtual void receive(Message* msg) {};

	virtual void save(json& file) {};

private:
	int buildPrice_;
	int buyBuildPrice_;

};

REGISTER_TYPE(PriceTextBox)