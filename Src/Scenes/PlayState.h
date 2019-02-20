#pragma once
#include "GameState.h"
#include "SceneManager.h"
class  PlayState : public GameState
{
private:

public:
	PlayState();
	virtual ~PlayState();

	void update();
	void render();
	void handleInput();
};