#include "Button.h"
#include "SceneManager.h"
#include "HUDManager.h"
#include "InputManager.h"

Button::Button()
{
	nextState = "StateMainMenu";
	std::string text = "PLAY";

	HUDManager::instance()->createButton(0.5f, 0.5f, -50, -30, 100.0f, 50.0f, text, &Button::onClick, this); // &onClick if used the other function
}

Button::~Button()
{
}

void Button::load(json file)
{
	addParameter(nextState, file["nextState"]);

	std::string text = "PLAY";

	HUDManager::instance()->createButton(0.5f, 0.5f, 0.0f, 0.0f, 100.0f, 50.0f, text, &Button::onClick, this); // &onClick if used the other function
}



bool Button::handleEvent(unsigned int time)
{
	if (InputManager::getSingletonPtr()->isKeyDown("Ray"))
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
	else
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
	}
	
	return true;
}

bool Button::onClick(const CEGUI::EventArgs& e)
{
	SceneManager::instance()->changeState(nextState);
	return true;
}
