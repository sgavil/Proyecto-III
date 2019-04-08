#include "ButtonExit.h"

#include "HUDManager.h"
#include "SceneManager.h"

ButtonExit::ButtonExit()
{
}

ButtonExit::~ButtonExit()
{
}

void ButtonExit::load(json file)
{
	float posX, posY, sizeX, sizeY, offsetX, offsetY;
	posX = posY = sizeX = sizeY = offsetX = offsetY = 0;

	std::string text;
	addParameter(text, file["text"]);

	addParameter(posX, file["posX"]);
	addParameter(posY, file["posY"]);
	addParameter(sizeX, file["sizeX"]);
	addParameter(sizeY, file["sizeY"]);
	addParameter(offsetX, file["offsetX"]);
	addParameter(offsetY, file["offsetY"]);


	HUDManager::instance()->createButton(posX, posY, offsetX, offsetY, sizeX, sizeY, text, &ButtonExit::onClick, this);
}

bool ButtonExit::handleEvent(unsigned int time)
{
	return true;
}

bool ButtonExit::onClick(const CEGUI::EventArgs & e)
{
	SceneManager::instance()->exitGame();

	return true;
}
