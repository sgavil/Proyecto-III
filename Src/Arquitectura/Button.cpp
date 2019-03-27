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

bool Button::handleEvent(unsigned int time)
{
	return true;
}
