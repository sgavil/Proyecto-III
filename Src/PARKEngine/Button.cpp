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
	addParameter(nextState, file["nextState"]);

	std::string text;
	addParameter(text, file["text"]);

	float posX = file["posX"];
	HUDManager::instance()->createButton(posX, 0.5, -50, 0, 100, 50, text, &Button::onClick, this); // &onClick if used the other function
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
	int count = HUDManager::instance()->activeWindow->getChildCount();
	SceneManager::instance()->changeState(nextState);
	return true;
}
