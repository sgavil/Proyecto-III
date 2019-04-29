#include "TextBox.h"

TextBox::TextBox()
{
	type = "TaharezLook/StaticText";
}

TextBox::~TextBox()
{
}

void TextBox::load(json file)
{
	Widget::load(file);

	addParameter(text, file["text"]);

	window->setText(text);
}

void TextBox::setText(std::string s)
{
	window->setText(s);
}
