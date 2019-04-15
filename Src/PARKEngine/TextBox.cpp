#include "TextBox.h"

TextBox::TextBox()
{

}

TextBox::~TextBox()
{

}

void TextBox::load(json file)
{
	float posX, posY, sizeX, sizeY, offsetX, offsetY;
	posX = posY = sizeX = sizeY = offsetX = offsetY = 0;

	text = file["Text"].get<std::string>();

	posX = file["posX"];
	posY = file["posY"];

	sizeX = file["sizeX"];
	sizeY = file["sizeY"];
	
	offsetX = file["offsetX"];
	offsetY = file["offsetY"];

	HUDManager::instance()->createText(posX, posY, offsetX, offsetY, sizeX, sizeY, text);
}
