#include "Button.h"
#include <Scenes/SceneManager.h>


Button::Button()
{
}

Button::~Button()
{
}

void Button::load(json file)
{
	nextState = file["nextState"];
}

bool Button::handleEvent(Event e, unsigned int time)
{

	// On button click:
	SceneManager::instance()->changeState(nextState);
	
	return false;
}
