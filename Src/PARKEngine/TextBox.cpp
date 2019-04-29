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
	centreText("Centre");


}

void TextBox::centreText(std::string s)
{
	window->setProperty("HorzFormatting", s + "Aligned");
}

void TextBox::setBackgroundVisible(string boolean)
{
	window->setProperty("BackgroundEnabled", boolean);
	window->setProperty("FrameEnabled", boolean);
}
