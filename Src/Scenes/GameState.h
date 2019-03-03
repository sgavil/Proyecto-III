#pragma once
#include <list>
#include "Arquitectura\Entity.h"


class GameState
{
protected:
	std::list<Component*> scene; // Componentes en la escena

	virtual void start() = 0;
public:
	GameState();
	virtual ~GameState();

	virtual void update(unsigned int time);
	virtual void render(unsigned int time);
	virtual void handleInput();
};