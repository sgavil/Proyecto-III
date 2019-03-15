#include "Transform.h"



Transform::Transform()
{
	//Nombre del componente
	name_ = Name::TransformComp;

}


Transform::~Transform()
{
}

void Transform::update(unsigned int time)
{

}

bool Transform::handleEvent(SDL_Event* e, unsigned int time)
{
	if (e->type == SDL_KEYDOWN)
	{
		//El control 0 estar parado, el 1 izda, el 2 dcha, el 3 arriba y el 4 abajo
		if (e->key.keysym.sym == SDLK_SPACE)
		{
			//foo
		}
	}
	return false;
}
