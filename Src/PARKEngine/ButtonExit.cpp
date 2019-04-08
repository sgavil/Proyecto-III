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
	std::string text;
	addParameter(text, file["text"]);

	float posX = file["posX"];
	HUDManager::instance()->createButton(posX, 0.5, -50, 0, 100, 50, text, &ButtonExit::onClick, this); // &onClick if used the other function
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
