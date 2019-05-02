#include "PriceTextBox.h"

PriceTextBox::PriceTextBox()
{
}

PriceTextBox::~PriceTextBox()
{
}

void PriceTextBox::load(json file)
{
	TextBox::load(file);

	buildPrice_ = file["Price"];
	buyBuildPrice_ = file["BuyPrice"];
}