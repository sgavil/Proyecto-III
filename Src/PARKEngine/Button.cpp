#include "Button.h"
#include "SceneManager.h"
#include "CallbackManager.h"
#include "HUDManager.h"
#include "InputManager.h"

Button::Button(): callbackParam("")
{
}

Button::~Button()
{
}

void Button::load(json file)
{
	float posX, posY, sizeX, sizeY, offsetX,offsetY;
	posX = posY = sizeX = sizeY = offsetX = offsetY = 0;

	addParameter(callback, file["callback"]);
	addParameter(callbackParam, file["parameter"]);

	std::string name = getEntity()->getName();
	
	std::string text;
	addParameter(text, file["text"]);

	addParameter(posX, file["posX"]);
	addParameter(posY, file["posY"]);
	addParameter(sizeX, file["sizeX"]);
	addParameter(sizeY, file["sizeY"]);
	addParameter(offsetX, file["offsetX"]);
	addParameter(offsetY, file["offsetY"]);


	HUDManager::instance()->createButton(name, posX, posY, offsetX, offsetY, sizeX, sizeY, text, &Button::onClick, this);
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
	CallbackManager::instance()->getCallback(callback)(callbackParam);
	return true;
}
