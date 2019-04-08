#include "Button.h"
#include "SceneManager.h"
#include "HUDManager.h"
#include "InputManager.h"

Button::Button()
{
	
}

Button::~Button()
{
}

void Button::load(json file)
{
	float posX, posY, sizeX, sizeY, offsetX,offsetY;
	posX = posY = sizeX = sizeY = offsetX = offsetY = 0;

	addParameter(nextState, file["nextState"]);

	std::string text;
	addParameter(text, file["text"]);

	addParameter(posX, file["posX"]);
	addParameter(posY, file["posY"]);
	addParameter(sizeX, file["sizeX"]);
	addParameter(sizeY, file["sizeY"]);
	addParameter(offsetX, file["offsetX"]);
	addParameter(offsetY, file["offsetY"]);


	HUDManager::instance()->createButton(posX, posY, offsetX, offsetY, sizeX, sizeY, text, &Button::onClick, this);
}



bool Button::handleEvent(unsigned int time)
{
	if (InputManager::getSingletonPtr()->isKeyDown("Ray"))
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
	else
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
	}
	
	return false;
}

bool Button::onClick(const CEGUI::EventArgs& e)
{
	int count = HUDManager::instance()->activeWindow->getChildCount();
	SceneManager::instance()->changeState(nextState);
	return true;
}
