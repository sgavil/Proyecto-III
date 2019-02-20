#pragma once
#include <list>
#include "Arquitectura\Entity.h"
//#include "SceneManager.h"

class GameState
{
protected:
	std::list<Entity*> scene; // Entities in the current scene
public:
	GameState();
	virtual ~GameState();

	virtual void update();
	virtual void render();
	virtual void handleInput();
};